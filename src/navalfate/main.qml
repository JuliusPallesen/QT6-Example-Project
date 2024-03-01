import QtQuick
import QtQuick.Controls.Universal
import QtQuick.Layouts

ApplicationWindow {
    id: mainwindow
    width: 1280
    height: 720
    visible: true

    Universal.theme: Universal.Dark

    menuBar: MenuBar {
        id: headermenu
        Menu {
            // Export a file handler class from C++ to use here
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&New...")
            }
            MenuItem {
                text: qsTr("&Open...")
            }
            MenuItem {
                text: qsTr("&Save")
            }
            MenuSeparator {
            }
            MenuItem {
                text: qsTr("&Quit")
            }
        }
        Menu {
            title: qsTr("&Help")
            MenuItem {
                text: qsTr("&Print Help")
            }
        }
    }

    footer: Frame {
        id: footerbar
        Row {
            Label {
                text: "Naval Fate\t"
                color: "SlateGrey"
            }

            Label {
                text: "Version 0.0.0.0.0.0.1\t"
                color: "SlateGrey"
            }
        }
    }

    Item {
        id: content
        anchors.fill: parent
        property int viewPercent: 70

        Item {
            id: field
            anchors {
                left: content.left
                top: content.top
                bottom: content.bottom
                right: content.right
                rightMargin: (content.width / 100) * (100 - content.viewPercent)
            }

            Grid {
                id: battlefield
                rows: g_gridsize
                columns: g_gridsize
                anchors.fill: parent
                Repeater {
                    model: g_gridsize * g_gridsize
                    Rectangle {
                        property int i
                        function determineColor(index, g_gridsize) {
                            var v1 = Math.floor(index / g_gridsize) % 2 === 0 ? 0 : 1;
                            return (index + v1) % 2 === 0 ? "black" : "white";
                        }

                        width: battlefield.width / g_gridsize
                        height: battlefield.height / g_gridsize
                        color: determineColor(index, g_gridsize)

                        Component.onCompleted: {
                            i = index;
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                console.log("x: " + i % g_gridsize + " y: " + Math.floor(i / g_gridsize));
                            }
                        }
                    }
                }
            }
        }
        Item {
            id: submenus
            anchors {
                left: content.left
                leftMargin: (content.width / 100) * content.viewPercent
                top: content.top
                bottom: content.bottom
                right: content.right
            }
            TabBar {
                id: tabs
                width: parent.width
                Repeater {
                    model: ["Ships", "Mines", "HighScores"]

                    TabButton {
                        text: qsTr(modelData)
                        width: implicitWidth
                    }
                }
            }

            StackLayout {
                anchors {
                    bottom: parent.bottom
                    left: parent.left
                    right: parent.right
                    top: tabs.bottom
                }
                currentIndex: tabs.currentIndex

                Rectangle {
                    anchors.fill: parent
                    color: "gray"
                    Column {
                        id: shipMenu
                        Repeater {
                            model: 5
                            delegate: Row {
                                Label {
                                    text: "abc" + index
                                    height: implicitHeight
                                    width: implicitWidth
                                }

                                TextField {
                                    height: implicitHeight
                                    width: implicitWidth
                                }
                            }
                        }
                    }
                }

                Rectangle {
                    anchors.fill: parent
                    color: "black"
                }

                Rectangle {
                    anchors.fill: parent
                    color: "gray"
                }
            }
        }
    }
}
