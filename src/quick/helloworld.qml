import QtQuick 2.0
import QtQuick.Controls
import backend.invokable

ApplicationWindow {
    id: window
    visible: true
    title: qsTr("Playground")
    height: 480
    width: 640

    property bool day: true

    Rectangle {
        id: sky
        color: window.day ? "lightblue" : "darkblue"
        anchors.fill: parent

        HelloWorldText {
            anchors {
                top: parent.top
                left: parent.left
                topMargin: 50
                leftMargin: 50
            }
            width: 100
            height: 20
        }

        Rectangle {
            id: grass
            x: parent.x
            y: (parent.y + (parent.height / 2))
            color: window.day ? "green" : "darkgreen"
            width: parent.width
            height: (parent.height - y)

            Image {
                id: logo
                property int amount_clicked: 0
                source: "./zühlke_logo.png"
                width: 100
                height: 100
                anchors {
                    bottom: parent.bottom
                    right: parent.right
                    bottomMargin: 10
                    rightMargin: 10
                }

                Invokable {
                    id: backend
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        logo.amount_clicked = logo.amount_clicked + 1;
                        backend.setVal(logo.amount_clicked);
                        console.log(backend.getVal());
                    }
                }
            }
        }

        Item {
            id: sun
            anchors {
                top: sky.top
                topMargin: 100
                right: sky.right
                rightMargin: 100
            }

            Rectangle {
                id: sunBody
                width: 50
                height: 50
                color: window.day ? "yellow" : "lightgrey"
                radius: (width / 2)
                anchors.centerIn: parent

                MouseArea {
                    anchors.fill: sunBody
                    onClicked: {
                        window.day = window.day ? false : true;
                    }
                }

                Item {
                    id: beams
                    visible: window.day ? true : false
                    property int beamWidth: 6
                    property int beamHeight: 40
                    x: (sunBody.width / 2) - (beamWidth / 2)
                    y: sunBody.height / 2
                    Repeater {
                        model: 12
                        Rectangle {
                            width: beams.beamWidth
                            height: beams.beamHeight

                            color: sunBody.color

                            transform: Rotation {
                                origin.x: sunBody.x + sunBody.width / 2
                                origin.y: sunBody.y + sunBody.height / 2
                                angle: (360 / 12) * index
                            }
                        }
                    }
                }
            }
        }
    }
}
