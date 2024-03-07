import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Universal

Popup {
    id: alarmRinging
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
                source: "qrc:/QtExampleProject/resource/clock_black.png"
                height: parent.height
                fillMode: Image.PreserveAspectFit
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
        Slider {
            id: unlockSlider
            anchors {
                horizontalCenter: parent.horizontalCenter
                margins: parent.width * .05
                top: clockItem.bottom
            }
            from: 0
            to: 100
            value: 0

            onValueChanged: {
                if (value === to) {
                    alarmRinging.close();
                }
                value = from;
            }
        }
    }
}
