import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

ApplicationWindow {
    width: 480
    height: 720
    title: "My Alarm App"
    visible: true

    Universal.theme: Universal.Light
    Universal.accent: Universal.Cobalt

    EditAlarm {
        id: editPopup
    }

    AlarmRinging {
        id: alarmRinging
    }

    Rectangle {
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
                    editPopup.init(model);
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
