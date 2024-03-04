import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ItemDelegate {
    id: root
    readonly property ListView __lv: ListView.view
    width: parent.width

    MouseArea {
        Layout.fillHeight: true
        Layout.fillWidth: true
        onClicked: {
            console.log(__lv.id)
            __lv.currentIndex = index;
        }
    }
    contentItem: RowLayout {
        id: alarmRow
        ColumnLayout {
            Label {
                text: model.name
            }
            Label {
                text: {
                    return `${hours}:${String(minutes).padStart(2, '0')}`;
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
