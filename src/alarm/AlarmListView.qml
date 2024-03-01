import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ItemDelegate {
    id: root
    width: parent.width
    contentItem: ColumnLayout {
        RowLayout {
            id: alarmRow
            ColumnLayout {
                Label {
                    text: model.name
                }
                Label {
                    text: {
                        return String(model.hours) + ":" + String(model.minutes);
                    }
                }
            }
            Item {
                id: placeholder
                Layout.fillWidth: true
            }
            Switch {
                id: onOffSwitch
                checked: model.on
                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                onClicked: model.on = checked
            }
        }
    }
}
