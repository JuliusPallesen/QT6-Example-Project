import Alarm
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: popup
    visible: false
    property var alarm
    readonly property var a_name: alarm.name
    readonly property int a_hours: alarm.hours
    readonly property int a_minutes: alarm.minutes
    readonly property bool a_repeating: alarm.repeating

    width: parent.width
    height: parent.height

    Component {
        id: delegateComponent

        Label {
            text: modelData
            font: Tumbler.tumbler.font
            opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    Item {
        anchors.fill: parent
        anchors.margins: 50
        Rectangle {
            visible: true
            color: "white"
            anchors.fill: parent

            ColumnLayout {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 100
                TextInput {
                    width: implicitWidth
                    text: {
                        return popup.a_name;
                    }
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    onTextChanged: popup.alarm.name = text
                }
                Item {
                }
                RowLayout {
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Label {
                        text: "hours"
                    }
                    Label {
                        text: "minutes"
                    }
                }
                Item {
                }
                RowLayout {
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Tumbler {
                        id: hoursTumbler
                        model: 24
                        delegate: delegateComponent
                        currentIndex: {
                            return popup.a_hours;
                        }
                        onCurrentIndexChanged: popup.alarm.hours = currentIndex
                    }
                    Tumbler {
                        id: minutesTumbler
                        model: 60
                        delegate: delegateComponent
                        currentIndex: {
                            return popup.a_minutes;
                        }
                        onCurrentIndexChanged: popup.alarm.minutes = currentIndex
                    }
                }
                RowLayout {
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Label {
                        text: "repeating"
                    }
                    CheckBox {
                        id: repeatingBox
                        checked: {
                            return popup.a_repeating;
                        }
                        onClicked: popup.alarm.repeating = checked
                    }
                }
                RowLayout {
                    Button {
                        text: "Save"
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        onClicked: {
                            popup.close();
                        }
                    }
                }
            }
        }
    }
}
