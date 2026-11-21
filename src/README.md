# Yasumi

Gentle break reminder that helps you avoid mindlessly skipping breaks.

A Qt 6 + QML desktop app for **Wayland (Hyprland)** that **seizes the whole
screen** on break time. Built as a spiritual sibling of
[AllanChain/sane-break](https://github.com/AllanChain/sane-break) but stripped
down and rebuilt for this desktop: single break type, CLI control, a
`Super+Shift+B` manual-break shortcut, and an AUR-ready install target.

## Key concept: full-screen seizure

Unlike a normal notification window, Yasumi's break overlay **claims a
compositor protocol** (`wlr_layer_shell_v1`) so it sits *above everything* and
**captures mouse and keyboard input** — you cannot click through it.

- **Layer:** `WlrLayer.Overlay` (topmost, no decorations)
- **Keyboard focus:** `WlrKeyboardFocus.None` during a break (compositor does
  not route keys to the app; the overlay consumes input)
- **Anchors:** fill the entire screen
- **Exclusive zone:** `-1` (claim all pixels)
- **Margins:** `0,0,0,0` (no gaps)

If the layer-shell protocol is unavailable, the app refuses to start with a
clear, actionable error rather than showing a partial window.

## Stack

- **UI:** Qt 6 QML (QtQuick) + the `Quickshell.Wayland._WlrLayerShell` QML plugin
- **Logic:** C++17 (state machine, CLI control, preferences)
- **Build:** CMake 3.16+, Qt 6.12
- **Deploy:** Linux native install + AUR (`PKGBUILD`)

## Structure

```
yasumi/
├── CMakeLists.txt
├── README.md
├── PKGBUILD                    # AUR package
├── src/
│   ├── main.cpp                # Entry point
│   ├── yasumiapp.cpp/.h        # App state machine + CLI control
│   ├── break-window.cpp/.h     # On-screen overlay
│   ├── preferences.cpp/.h      # Settings
│   ├── cli.cpp/.h              # CLI control (CLI11)
│   └── main.qml                # Root QML (contains WlrLayershell)
├── qml/
│   ├── break-window.qml        # Break overlay UI
│   └── ...
└── resources/icons/
    └── yasumi.png
```

## Build

    mkdir build && cd build
    cmake ..
    make -j$(nproc)
    sudo make install

## Run

    yasumi

## CLI control

    yasumi break-now        # start a break immediately
    yasumi status           # show current status (JSON)
    yasumi pause            # pause breaks
    yasumi resume           # resume breaks
    yasumi --version        # version

## Keyboard shortcut

`Super+Shift+B` starts a break immediately (when not already breaking).

## AUR

    git clone https://aur.archlinux.org/yasumi.git
    cd yasumi
    makepkg -si
