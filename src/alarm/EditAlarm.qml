import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: popup
    visible: false
    property var alarm //TODO: Fix binding loop somehow if possible
    readonly property var a_name: alarm ? alarm.name : ""
    readonly property int a_hours: alarm ? alarm.hours : 0
    readonly property int a_minutes: alarm ? alarm.minutes : 0
    readonly property bool a_repeating: alarm ? alarm.repeating : false

    width: parent.width
    height: parent.height

    Component {
        id: delegateComponent

        Label {
            text: modelData
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
                    id: nameText
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    width: implicitWidth
                    text: popup.a_name
                    font.pixelSize: 13
                    onTextChanged: popup.alarm.name = text
                }
                RowLayout {
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Tumbler {
                        id: hoursTumbler
                        model: 24
                        delegate: Label {
                            text: modelData
                            opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        currentIndex: {
                            return popup.a_hours;
                        }
                        onCurrentIndexChanged: popup.alarm ? popup.alarm.hours = currentIndex : 0
                    }
                    Label {
                        text: ":"
                    }
                    Tumbler {
                        id: minutesTumbler
                        model: 60
                        delegate: Label {
                            text: String(modelData).padStart(2, '0')
                            opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        currentIndex: {
                            return popup.a_minutes;
                        }
                        onCurrentIndexChanged: popup.alarm ? popup.alarm.minutes = currentIndex : 0
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
                Button {
                    text: "Save"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    onClicked: {
                        popup.close();
                    }
                }
                //TODO: Add cancel button if possible
            }
        }
    }
}
