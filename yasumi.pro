QT += core gui quick qml widgets network

CONFIG += c++17
CONFIG += release
CONFIG += optimize_size

SOURCES += \
    src/main.cpp \
    src/yasumiapp.cpp \
    src/cli.cpp

HEADERS += \
    src/yasumiapp.h \
    src/cli.h

RESOURCES += resources.qrc

INCLUDEPATH += .
INCLUDEPATH += src
DEPENDPATH += .

QMAKE_CXXFLAGS += -fno-common
QMAKE_LFLAGS += -Wl,--no-undefined

TARGET = yasumi

# Install rules. qmake stages under INSTALL_ROOT (makepkg sets it to $pkgdir).
target.path = /usr/bin
INSTALLS += target

data.path = /usr/share/yasumi
data.files = qml/Settings.qml qml/Overlay.qml resources/icons/yasumi.svg resources/icons/yasumi.png
INSTALLS += data

desktop.path = /usr/share/applications
desktop.files = yasumi.desktop
INSTALLS += desktop

# Start in the tray on login.
autostart.path = /etc/xdg/autostart
autostart.files = yasumi.desktop
INSTALLS += autostart

icon.path = /usr/share/icons/hicolor/scalable/apps
icon.files = resources/icons/yasumi.svg
INSTALLS += icon
