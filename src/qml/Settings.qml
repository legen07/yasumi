import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

// Settings + dashboard window. Shown when the tray icon is clicked.
Window {
    id: settingsWindow
    objectName: "settingsWindow"
    title: "Yasumi Settings"
    width: 460
    height: 600
    minimumWidth: 420
    minimumHeight: 540
    visible: false
    color: "#101216"

    readonly property color accent: "#4cc2ff"
    readonly property color fg: "#e8eaed"
    readonly property color muted: "#9aa0a6"
    readonly property color card: "#1a1d23"

    function stateLabel() {
        switch (controller.state) {
        case "breaking": return "On a break"
        case "paused":   return "Paused"
        case "disabled": return "Scheduler disabled"
        default:         return "Next break in"
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 22
        spacing: 16

        // Header
        RowLayout {
            Layout.fillWidth: true
            Text {
                text: "Yasumi"
                color: settingsWindow.fg
                font.pixelSize: 26
                font.bold: true
                Layout.fillWidth: true
            }
            Text {
                text: "v1.0.0"
                color: settingsWindow.muted
                font.pixelSize: 13
            }
        }

        // Dashboard card
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 150
            radius: 14
            color: settingsWindow.card

            ColumnLayout {
                anchors.centerIn: parent
                spacing: 6
                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: settingsWindow.stateLabel()
                    color: settingsWindow.muted
                    font.pixelSize: 15
                }
                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: controller.countdown
                    color: controller.breaking ? settingsWindow.accent : settingsWindow.fg
                    font.pixelSize: 52
                    font.bold: true
                    font.family: "monospace"
                }
                ProgressBar {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 260
                    visible: controller.breaking
                    from: 0; to: 1
                    value: controller.progress
                }
            }
        }

        // Action buttons
        RowLayout {
            Layout.fillWidth: true
            spacing: 10
            Button {
                Layout.fillWidth: true
                text: "Break Now"
                onClicked: controller.breakNow()
            }
            Button {
                Layout.fillWidth: true
                text: controller.state === "paused" ? "Resume" : "Pause"
                onClicked: controller.togglePause()
            }
        }

        // Settings card
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 14
            color: settingsWindow.card

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 18
                spacing: 14

                Text {
                    text: "Settings"
                    color: settingsWindow.fg
                    font.pixelSize: 17
                    font.bold: true
                }

                RowLayout {
                    Layout.fillWidth: true
                    Text { text: "Break every"; color: settingsWindow.fg; font.pixelSize: 15; Layout.fillWidth: true }
                    SpinBox {
                        id: intervalSpin
                        from: 1; to: 180
                        value: Math.max(1, Math.round(controller.interval / 60))
                        onValueModified: controller.setInterval(value * 60)
                    }
                    Text { text: "min"; color: settingsWindow.muted; font.pixelSize: 14 }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Text { text: "Break lasts"; color: settingsWindow.fg; font.pixelSize: 15; Layout.fillWidth: true }
                    SpinBox {
                        id: durationSpin
                        from: 1; to: 60
                        value: Math.max(1, Math.round(controller.duration / 60))
                        onValueModified: controller.setDuration(value * 60)
                    }
                    Text { text: "min"; color: settingsWindow.muted; font.pixelSize: 14 }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Text { text: "Enable scheduler"; color: settingsWindow.fg; font.pixelSize: 15; Layout.fillWidth: true }
                    Switch {
                        checked: controller.enabled
                        onToggled: controller.enabled = checked
                    }
                }

                Text {
                    Layout.fillWidth: true
                    wrapMode: Text.WordWrap
                    text: "When the countdown reaches zero, Yasumi covers the whole screen and captures input until the break ends. Super+Shift+B starts a break any time."
                    color: settingsWindow.muted
                    font.pixelSize: 12
                }
            }
        }
    }
}
