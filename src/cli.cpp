#include "cli.h"

#include <QCoreApplication>
#include <QLocalSocket>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDir>
#include <unistd.h>

QString yasumiSocketName()
{
    // Use a fixed absolute path in XDG_RUNTIME_DIR so the tray instance and
    // every CLI invocation agree regardless of TMPDIR (which differs between
    // a login session, a terminal, and a compositor keybind).
    QString runtime = QString::fromLocal8Bit(qgetenv("XDG_RUNTIME_DIR"));
    if (runtime.isEmpty())
        runtime = QDir::tempPath();
    return runtime + QStringLiteral("/yasumi-%1.sock").arg((uint)getuid());
}

bool isCliCommand(const QString &cmd)
{
    static const QStringList cmds = {
        "break-now", "end-break", "status", "pause", "resume",
        "enable-break", "disable-break", "enable", "disable",
        "set-interval", "set-duration", "quit"
    };
    return cmds.contains(cmd);
}

int runCliCommand(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Rebuild the command line (everything after argv[0]).
    QStringList parts;
    for (int i = 1; i < argc; ++i) parts << QString::fromLocal8Bit(argv[i]);
    const QByteArray payload = (parts.join(' ') + "\n").toUtf8();

    QLocalSocket sock;
    sock.connectToServer(yasumiSocketName());
    if (!sock.waitForConnected(1500)) {
        QTextStream(stderr) << "yasumi: no running instance found (start the tray app first)\n";
        return 1;
    }

    sock.write(payload);
    if (!sock.waitForBytesWritten(1500)) {
        QTextStream(stderr) << "yasumi: failed to send command\n";
        return 1;
    }

    QByteArray reply;
    while (sock.waitForReadyRead(2000)) {
        reply += sock.readAll();
        if (reply.contains('\n')) break;
    }
    reply += sock.readAll();

    QTextStream(stdout) << QString::fromUtf8(reply).trimmed() << "\n";
    sock.disconnectFromServer();
    return 0;
}
