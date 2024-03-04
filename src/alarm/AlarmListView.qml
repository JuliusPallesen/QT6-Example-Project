import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Alarm

ItemDelegate {
    id: root
    signal alarmEdit
    readonly property ListView __lv: ListView.view
    width: parent.width

    Rectangle {
        color: "transparent"
        border.color: __lv.currentIndex == index ? "grey" : "transparent"
        border.width: 2
        anchors.fill: parent
        radius: 10

        MouseArea {
            anchors.fill: parent
            onClicked: {
                __lv.currentIndex = index;
            }
            onDoubleClicked: {
                root.alarmEdit();
            }
            onPressAndHold: {
                root.alarmEdit();
            }
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
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    model.repeating = !model.repeating;
                }
            }
            Image {
                height: onOffSwitch.height
                fillMode: Image.PreserveAspectFit
                Layout.alignment: Qt.AlignTop | Qt.AlignRight
                source: model.repeating ? "repeating.jpg" : "not_repeating.jpg"
            }
        }

        Switch {
            id: onOffSwitch
            checked: model.on
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            onClicked: model.on = checked
        }
    }
}
