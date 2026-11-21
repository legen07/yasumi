#ifndef CLI_H
#define CLI_H

#include <QString>

// Shared local-socket name for the running Yasumi instance (per-user).
QString yasumiSocketName();

// True if argv[1] is a control command that should be sent to the running
// instance rather than starting the GUI.
bool isCliCommand(const QString &cmd);

// Connect to the running instance, send the command, print the JSON reply.
// Returns a process exit code. Uses QCoreApplication (no display needed).
int runCliCommand(int argc, char *argv[]);

#endif // CLI_H
