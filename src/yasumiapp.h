#ifndef YASUMIAAPP_H
#define YASUMIAAPP_H

#include <QObject>
#include <QTimer>
#include <QSettings>
#include <QLocalServer>
#include <QLocalSocket>
#include <QString>

// YasumiApp is the break controller: it owns the schedule, the countdown,
// pause/resume, persisted settings, and a local-socket IPC server that the
// `yasumi <command>` CLI talks to. The QML windows bind to its properties.
class YasumiApp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString state READ state NOTIFY stateChanged)
    Q_PROPERTY(int remaining READ remaining NOTIFY remainingChanged)
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(bool breaking READ breaking NOTIFY stateChanged)
    Q_PROPERTY(QString countdown READ countdown NOTIFY remainingChanged)
    Q_PROPERTY(double progress READ progress NOTIFY remainingChanged)

public:
    explicit YasumiApp(QObject *parent = nullptr);
    ~YasumiApp() override;

    QString state() const;          // "idle" | "breaking" | "paused" | "disabled"
    int remaining() const;          // seconds left (to next break, or in break)
    int interval() const;           // seconds between breaks
    int duration() const;           // seconds a break lasts
    bool enabled() const;
    bool breaking() const;
    QString countdown() const;      // mm:ss of remaining
    double progress() const;        // 0..1 through the current break

    void setInterval(int seconds);
    void setDuration(int seconds);
    void setEnabled(bool on);

    Q_INVOKABLE void breakNow();
    Q_INVOKABLE void endBreak();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void resume();
    Q_INVOKABLE void togglePause();

    QString statusJson() const;

signals:
    void stateChanged();
    void remainingChanged();
    void intervalChanged();
    void durationChanged();
    void enabledChanged();
    void showOverlay();
    void hideOverlay();

private slots:
    void tick();
    void onIpcConnection();

private:
    void loadSettings();
    void saveSettings();
    void startIdleCountdown();
    void beginBreak();
    void finishBreak();
    void handleIpcCommand(const QString &line, QLocalSocket *sock);

    enum State { Idle, Breaking, Paused };
    State m_state = Idle;
    State m_stateBeforePause = Idle;
    bool m_enabled = true;
    int m_interval = 1500;   // 25 min
    int m_duration = 300;    // 5 min
    int m_remaining = 1500;
    QTimer m_tick;
    QSettings *m_settings = nullptr;
    QLocalServer *m_server = nullptr;
};

#endif // YASUMIAAPP_H
