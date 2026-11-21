import QtQuick
import QtQuick.Controls
import QtQuick.Window

// Full-screen break overlay. Seizes the entire display and captures input so
// clicks cannot fall through to the apps underneath. Shown by the controller
// when a break starts; hidden when it ends.
Window {
    id: overlayWindow
    objectName: "overlayWindow"
    title: "Yasumi Break"
    visible: false
    // NOTE: do NOT add Qt.BypassWindowManagerHint — it makes clicks pass
    // through to underlying windows on Hyprland (verified by test).
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    visibility: Window.FullScreen
    color: "#000000"

    function geo() {
        if (screen && screen.virtualGeometry && screen.virtualGeometry.width > 0)
            return screen.virtualGeometry;
        return Qt.rect(0, 0, 1920, 1080);
    }
    x: geo().x
    y: geo().y
    width: geo().width
    height: geo().height

    Rectangle {
        anchors.fill: parent
        color: "#0b0b0e"

        Column {
            anchors.centerIn: parent
            spacing: 26

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "TIME TO REST"
                color: "#f5f5f5"
                font.pixelSize: 46
                font.bold: true
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: controller.countdown
                color: "#4cc2ff"
                font.pixelSize: 96
                font.bold: true
                font.family: "monospace"
            }

            ProgressBar {
                anchors.horizontalCenter: parent.horizontalCenter
                width: 420
                from: 0; to: 1
                value: controller.progress
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Step away from the screen. Breathe. Stretch."
                color: "#bdbdbd"
                font.pixelSize: 22
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "End Break"
                onClicked: controller.endBreak()
            }
        }
    }
}
