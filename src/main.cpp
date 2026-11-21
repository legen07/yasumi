// Yasumi — a sane-break style app for Wayland.
// Lives in the system tray. A countdown runs in the background; when it hits
// zero the full-screen break overlay seizes the display. Clicking the tray
// icon opens the settings / dashboard window. `yasumi <command>` controls the
// running instance over a local socket.
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QDebug>
#include <QQmlError>
#include <cstdio>

#include "yasumiapp.h"
#include "cli.h"

#define YASUMI_VERSION "1.0.0"

static void printHelp()
{
    std::printf(
        "Yasumi %s — full-screen break reminder for Wayland\n\n"
        "Usage: yasumi [command]\n\n"
        "With no command, Yasumi runs in the system tray and counts down to the\n"
        "next break. Click the tray icon to open settings.\n\n"
        "Commands (control the running tray instance):\n"
        "  break-now             Start a break immediately\n"
        "  end-break             End the current break\n"
        "  status                Print state / countdown as JSON\n"
        "  pause                 Pause the schedule\n"
        "  resume                Resume the schedule\n"
        "  enable-break          Enable the scheduler\n"
        "  disable-break         Disable the scheduler\n"
        "  set-interval <sec>    Seconds between breaks\n"
        "  set-duration <sec>    Seconds a break lasts\n"
        "  quit                  Quit the tray instance\n"
        "  --version, -v         Show version\n"
        "  --help, -h            Show this help\n",
        YASUMI_VERSION);
}

static QQuickWindow *findWindow(QQmlApplicationEngine &engine, const QString &name)
{
    for (QObject *obj : engine.rootObjects()) {
        if (obj->objectName() == name)
            return qobject_cast<QQuickWindow *>(obj);
    }
    return nullptr;
}

int main(int argc, char *argv[])
{
    // Pure CLI / info invocations need no display and no GUI.
    if (argc > 1) {
        const QString first = QString::fromLocal8Bit(argv[1]);
        if (first == "--version" || first == "-v") {
            std::printf("yasumi %s\n", YASUMI_VERSION);
            return 0;
        }
        if (first == "--help" || first == "-h") { printHelp(); return 0; }
        if (isCliCommand(first)) return runCliCommand(argc, argv);
    }

    QApplication app(argc, argv);
    app.setApplicationName("yasumi");
    app.setOrganizationName("yasumi");
    app.setApplicationVersion(YASUMI_VERSION);
    app.setWindowIcon(QIcon(QStringLiteral(":/resources/icons/yasumi.png")));
    // Tray app: closing the settings window must not quit the process.
    QApplication::setQuitOnLastWindowClosed(false);

    YasumiApp controller;

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::warnings,
                     [](const QList<QQmlError> &errs) {
                         for (const QQmlError &e : errs)
                             qWarning() << "QML:" << e.toString();
                     });
    engine.rootContext()->setContextProperty(QStringLiteral("controller"), &controller);

    engine.load(QUrl(QStringLiteral("qrc:/qml/Settings.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/qml/Overlay.qml")));
    if (engine.rootObjects().isEmpty()) {
        qCritical() << "Failed to load Yasumi QML";
        return 1;
    }

    QQuickWindow *settings = findWindow(engine, QStringLiteral("settingsWindow"));
    QQuickWindow *overlay  = findWindow(engine, QStringLiteral("overlayWindow"));
    if (!settings || !overlay) {
        qCritical() << "Missing settings/overlay window" << (settings != nullptr) << (overlay != nullptr);
        return 1;
    }
    settings->hide();
    overlay->hide();

    auto showSettings = [settings]() {
        settings->show();
        settings->raise();
        settings->requestActivate();
    };

    // Overlay show/hide driven by the controller.
    QObject::connect(&controller, &YasumiApp::showOverlay, &app, [overlay]() {
        overlay->showFullScreen();
        overlay->raise();
        overlay->requestActivate();
    });
    QObject::connect(&controller, &YasumiApp::hideOverlay, &app, [overlay]() {
        overlay->hide();
    });

    // System tray.
    QSystemTrayIcon tray(QIcon(QStringLiteral(":/resources/icons/yasumi.png")), &app);
    tray.setToolTip(QStringLiteral("Yasumi — next break in %1").arg(controller.countdown()));
    QMenu menu;
    QAction *openAct   = menu.addAction(QStringLiteral("Open Yasumi"));
    QAction *breakAct  = menu.addAction(QStringLiteral("Break Now"));
    QAction *pauseAct  = menu.addAction(QStringLiteral("Pause"));
    menu.addSeparator();
    QAction *quitAct   = menu.addAction(QStringLiteral("Quit"));
    QObject::connect(openAct,  &QAction::triggered, &app, showSettings);
    QObject::connect(breakAct, &QAction::triggered, &controller, &YasumiApp::breakNow);
    QObject::connect(pauseAct, &QAction::triggered, &controller, &YasumiApp::togglePause);
    QObject::connect(quitAct,  &QAction::triggered, &app, &QApplication::quit);
    QObject::connect(&controller, &YasumiApp::stateChanged, &app, [&]() {
        pauseAct->setText(controller.state() == "paused" ? QStringLiteral("Resume")
                                                         : QStringLiteral("Pause"));
    });
    QObject::connect(&controller, &YasumiApp::remainingChanged, &app, [&]() {
        tray.setToolTip(controller.breaking()
            ? QStringLiteral("Yasumi — break: %1 left").arg(controller.countdown())
            : QStringLiteral("Yasumi — next break in %1").arg(controller.countdown()));
    });
    tray.setContextMenu(&menu);
    QObject::connect(&tray, &QSystemTrayIcon::activated, &app,
                     [&](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick)
            showSettings();
    });
    qDebug() << "yasumi: system tray available =" << QSystemTrayIcon::isSystemTrayAvailable();
    tray.show();
    qDebug() << "yasumi: tray visible =" << tray.isVisible();

    return app.exec();
}
