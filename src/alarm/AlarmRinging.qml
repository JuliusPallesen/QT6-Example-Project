import QtQuick
import QtQuick.Controls

Popup {
    id: alarmRing
    property var name: ""
    visible: false

    width: parent.width
    height: parent.height
    Item {
        anchors.fill: parent
        Label {
            anchors {
                horizontalCenter: parent.horizontalCenter
                margins: parent.width * .05
                bottom: nameLabel.top
            }
            font.pixelSize: 24
            font.bold: true
            text: timerbackend.currentTime
        }
        Label {
            id: nameLabel
            anchors {
                horizontalCenter: parent.horizontalCenter
                margins: parent.width * .05
                bottom: clockIcon.top
            }
            text: name
            font.pixelSize: 16
            font.bold: true
        }

        Image {
            id: clockIcon
            anchors {
                centerIn: parent
                left: parent.left
                right: parent.right
                margins: parent.width * .25
            }
            source: "clock.jpg"
        }
    }
}
