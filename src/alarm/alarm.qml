import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    //TODO: Use styles
    width: 480
    height: 720
    title: "My Alarm App"
    visible: true

    EditAlarm {
        id: editPopup
    }

    AlarmRinging {
        id: alarmRinging
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
                alarmRinging.name = alarmModel.get(i).name;
                alarmRinging.open();
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
                onAlarmDeleted: {
                    alarmModel.removeRows(index, 1);
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
                //TODO: open edit alarm with newly added Alarm if possible
            }
        }
    }
}
