import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ItemDelegate {
    id: root
    signal alarmEdit
    signal triggeredChanged
    readonly property ListView __lv: ListView.view
    width: parent.width

    Rectangle {
        color: "transparent"
        anchors.fill: parent
        border.color: __lv.currentIndex == index ? "grey" : "transparent"
        border.width: 2
        radius: 10
        z: 99
        MouseArea {

            anchors {
                fill: parent
                rightMargin: parent.width * .25
            }
            preventStealing: false
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
            Layout.fillWidth: true
        }
        Item {
            id: repeatingIcon
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            Layout.rightMargin: 30
            Image {
                height: onOffSwitch.height
                fillMode: Image.PreserveAspectFit
                source: model.repeating ? "repeating.jpg" : "not_repeating.jpg"
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
