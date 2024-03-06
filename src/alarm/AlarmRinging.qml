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
                bottom: clockItem.top
            }
            text: name
            font.pixelSize: 16
            font.bold: true
        }
        Item {
            id: clockItem
            width: parent.width / 2
            height: parent.width / 2
            anchors.centerIn: parent
            Image {
                id: clockIcon
                source: "clock.jpg"

                SequentialAnimation {
                    id: shakeAnimation
                    loops: Animation.Infinite
                    PropertyAnimation {
                        target: clockIcon
                        property: "x"
                        from: -2
                        to: 2
                        duration: 100
                    }
                    PropertyAnimation {
                        target: clockIcon
                        property: "y"
                        from: -2
                        to: 2
                        duration: 100
                    }
                }

                Component.onCompleted: {
                    shakeAnimation.start();
                }
            }
        }
    }
}
