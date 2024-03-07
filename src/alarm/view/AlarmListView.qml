import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

ItemDelegate {
    id: root
    clip: true
    signal alarmEdit
    signal triggeredChanged
    signal alarmDeleted
    readonly property ListView __lv: ListView.view
    width: parent.width

    Rectangle {
        color: "transparent"
        anchors.fill: parent
        border.color: __lv.currentIndex == index ? Universal.color(Universal.Blue) : "transparent"
        border.width: 2
        radius: 10
        z: 99
        MouseArea {
            id: rowArea
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            anchors {
                fill: parent
                rightMargin: parent.width * .25
            }
            preventStealing: false
            onClicked: mouse => {
                if (mouse.button == Qt.LeftButton) {
                    //TODO: Update to non-deprecated
                    __lv.currentIndex = index;
                } else {
                    contextMenu.open();
                }
            }
            Menu {
                id: contextMenu
                MenuItem {
                    text: "Edit"
                    onTriggered: root.alarmEdit()
                }
                MenuItem {
                    text: "Remove"
                    onTriggered: root.alarmDeleted()
                }
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
            Layout.fillWidth: true
        }
        Item {
            id: repeatingIcon
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            Layout.rightMargin: 30
            Image {
                height: onOffSwitch.height
                fillMode: Image.PreserveAspectFit
                source: model.repeating ? ":/qrc/resource/repeating_black.png" : ":/qrc/resource/repeating_grey.png" 
                MouseArea {
                    propagateComposedEvents: true
                    z: 100
                    anchors.fill: parent
                    preventStealing: true
                    onClicked: {
                        model.repeating = !model.repeating;
                    }
                }
            }
        }
        Switch {
            id: onOffSwitch
            z: 100
            checked: model.on
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            onClicked: model.on = checked
        }
    }
}
