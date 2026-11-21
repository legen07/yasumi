#include "yasumiapp.h"
#include "cli.h"

#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <unistd.h>

YasumiApp::YasumiApp(QObject *parent)
    : QObject(parent)
{
    loadSettings();
    m_remaining = m_interval;

    m_tick.setInterval(1000);
    connect(&m_tick, &QTimer::timeout, this, &YasumiApp::tick);

    // IPC server so `yasumi <command>` can control this running instance.
    m_server = new QLocalServer(this);
    const QString name = yasumiSocketName();
    QLocalServer::removeServer(name); // clear any stale socket from a crash
    if (!m_server->listen(name))
        qWarning() << "Yasumi IPC listen failed:" << m_server->errorString();
    connect(m_server, &QLocalServer::newConnection, this, &YasumiApp::onIpcConnection);

    if (m_enabled)
        m_tick.start();
}

YasumiApp::~YasumiApp()
{
    if (m_server) m_server->close();
}

void YasumiApp::loadSettings()
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir().mkpath(dir);
    m_settings = new QSettings(dir + "/yasumi.ini", QSettings::IniFormat, this);
    m_interval = m_settings->value("interval", 1500).toInt();
    m_duration = m_settings->value("duration", 300).toInt();
    m_enabled  = m_settings->value("enabled", true).toBool();
    if (m_interval < 5) m_interval = 5;
    if (m_duration < 5) m_duration = 5;
}

void YasumiApp::saveSettings()
{
    if (!m_settings) return;
    m_settings->setValue("interval", m_interval);
    m_settings->setValue("duration", m_duration);
    m_settings->setValue("enabled", m_enabled);
    m_settings->sync();
}

QString YasumiApp::state() const
{
    if (!m_enabled) return QStringLiteral("disabled");
    switch (m_state) {
    case Breaking: return QStringLiteral("breaking");
    case Paused:   return QStringLiteral("paused");
    default:       return QStringLiteral("idle");
    }
}

int YasumiApp::remaining() const { return m_remaining; }
int YasumiApp::interval() const { return m_interval; }
int YasumiApp::duration() const { return m_duration; }
bool YasumiApp::enabled() const { return m_enabled; }
bool YasumiApp::breaking() const { return m_state == Breaking; }

QString YasumiApp::countdown() const
{
    int s = m_remaining < 0 ? 0 : m_remaining;
    int m = s / 60, sec = s % 60;
    return QString("%1:%2").arg(m, 2, 10, QChar('0')).arg(sec, 2, 10, QChar('0'));
}

double YasumiApp::progress() const
{
    if (m_state != Breaking || m_duration <= 0) return 0.0;
    double p = 1.0 - (double)m_remaining / (double)m_duration;
    if (p < 0) p = 0; if (p > 1) p = 1;
    return p;
}

void YasumiApp::setInterval(int seconds)
{
    if (seconds < 5) seconds = 5;
    if (seconds == m_interval) return;
    m_interval = seconds;
    if (m_state == Idle) m_remaining = m_interval;
    saveSettings();
    emit intervalChanged();
    emit remainingChanged();
}

void YasumiApp::setDuration(int seconds)
{
    if (seconds < 5) seconds = 5;
    if (seconds == m_duration) return;
    m_duration = seconds;
    saveSettings();
    emit durationChanged();
}

void YasumiApp::setEnabled(bool on)
{
    if (on == m_enabled) return;
    m_enabled = on;
    if (!on) {
        if (m_state == Breaking) finishBreak();
        m_tick.stop();
    } else if (m_state != Paused) {
        m_tick.start();
    }
    saveSettings();
    emit enabledChanged();
    emit stateChanged();
}

void YasumiApp::breakNow() { beginBreak(); }

void YasumiApp::endBreak() { finishBreak(); }

void YasumiApp::pause()
{
    if (m_state == Paused) return;
    m_stateBeforePause = m_state;
    if (m_state == Breaking) emit hideOverlay();
    m_state = Paused;
    m_tick.stop();
    emit stateChanged();
}

void YasumiApp::resume()
{
    if (m_state != Paused) return;
    m_state = m_stateBeforePause;
    if (m_state == Breaking) emit showOverlay();
    if (m_enabled) m_tick.start();
    emit stateChanged();
}

void YasumiApp::togglePause()
{
    if (m_state == Paused) resume(); else pause();
}

void YasumiApp::beginBreak()
{
    m_state = Breaking;
    m_remaining = m_duration;
    if (!m_tick.isActive() && m_enabled) m_tick.start();
    emit stateChanged();
    emit remainingChanged();
    emit showOverlay();
}

void YasumiApp::finishBreak()
{
    m_state = Idle;
    m_remaining = m_interval;
    emit stateChanged();
    emit remainingChanged();
    emit hideOverlay();
}

void YasumiApp::tick()
{
    if (!m_enabled || m_state == Paused) return;
    if (m_remaining > 0) m_remaining--;
    if (m_remaining <= 0) {
        if (m_state == Breaking) finishBreak();
        else beginBreak();
    }
    emit remainingChanged();
}

QString YasumiApp::statusJson() const
{
    QJsonObject o;
    o["state"] = state();
    o["remaining"] = m_remaining;
    o["interval"] = m_interval;
    o["duration"] = m_duration;
    o["enabled"] = m_enabled;
    o["countdown"] = countdown();
    return QString::fromUtf8(QJsonDocument(o).toJson(QJsonDocument::Compact));
}

void YasumiApp::onIpcConnection()
{
    while (m_server->hasPendingConnections()) {
        QLocalSocket *sock = m_server->nextPendingConnection();
        connect(sock, &QLocalSocket::disconnected, sock, &QObject::deleteLater);
        connect(sock, &QLocalSocket::readyRead, this, [this, sock]() {
            const QByteArray data = sock->readAll();
            const QStringList lines = QString::fromUtf8(data).split('\n', Qt::SkipEmptyParts);
            for (const QString &line : lines)
                handleIpcCommand(line.trimmed(), sock);
        });
    }
}

void YasumiApp::handleIpcCommand(const QString &line, QLocalSocket *sock)
{
    const QStringList parts = line.split(' ', Qt::SkipEmptyParts);
    const QString cmd = parts.value(0);
    QJsonObject resp;
    bool ok = true;
    bool doQuit = false;

    if (cmd == "break-now")            { breakNow(); }
    else if (cmd == "end-break")       { endBreak(); }
    else if (cmd == "pause")           { pause(); }
    else if (cmd == "resume")          { resume(); }
    else if (cmd == "enable-break" || cmd == "enable")  { setEnabled(true); }
    else if (cmd == "disable-break" || cmd == "disable"){ setEnabled(false); }
    else if (cmd == "set-interval" && parts.size() > 1) { setInterval(parts[1].toInt()); }
    else if (cmd == "set-duration" && parts.size() > 1) { setDuration(parts[1].toInt()); }
    else if (cmd == "quit")            { doQuit = true; }
    else if (cmd == "status")          { /* reply is status below */ }
    else { ok = false; resp["error"] = "unknown command: " + cmd; }

    if (ok) {
        resp["success"] = true;
        resp["command"] = cmd;
        resp["state"] = state();
        resp["remaining"] = m_remaining;
        resp["countdown"] = countdown();
        if (cmd == "status") {
            resp["interval"] = m_interval;
            resp["duration"] = m_duration;
            resp["enabled"] = m_enabled;
        }
    } else {
        resp["success"] = false;
    }

    sock->write(QJsonDocument(resp).toJson(QJsonDocument::Compact) + "\n");
    sock->flush();
    sock->disconnectFromServer();

    if (doQuit) QCoreApplication::quit();
}
