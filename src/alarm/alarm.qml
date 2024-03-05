import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 480
    height: 720
    title: "My Alarm App"
    visible: true

    EditAlarm {
        id: editPopup
    }

    Rectangle {
        color: "grey"
        anchors {
            fill: parent
            margins: 50
        }

        Connections {
            target: alarmModel
            function onTriggeredAlarm(i) {
                console.log(i);
            //helloworld
            }
        }

        ListView {
            id: alarmsList
            anchors.fill: parent
            clip: true

            header: Label {
                x: parent.width / 2 - width / 2
                text: timerbackend.currentTime
            }

            model: alarmModel

            delegate: AlarmListView {
                onAlarmEdit: {
                    editPopup.alarm = model;
                    editPopup.open();
                }
                onTriggeredChanged: {
                    console.log(model.name);
                }
            }
        }

        Button {
            text: "Add"
            anchors {
                bottom: parent.bottom
                bottomMargin: 20
                horizontalCenter: parent.horizontalCenter
            }
            onClicked: {
                alarmModel.insertRows(alarmModel.rowCount(), 1);
            }
        }
    }
}
