import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Alarm

ApplicationWindow {
    width: 480
    height: 720
    title: "My Alarm App"
    visible: true

    Rectangle {
        color: "grey"
        anchors {
            fill: parent
            margins: 50
        }

        ListView {
            id: alarmsList
            anchors.fill: parent
            clip: true

            model: AlarmsModel {
                id: alarmModel
            }

            delegate: AlarmListView {
            }

            onCurrentIndexChanged: {
                console.log(currentIndex);
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
