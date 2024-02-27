import QtQuick
import QtQuick.Window
import Tile
import Qt.labs.qmlmodels

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("QML CPP M/V Demo")

    GridView {
        id: gridview
        anchors.fill: parent
        model: myObjects
        delegate: tilechooser

        DelegateChooser {
            id: tilechooser
            role: "tile_type"
            
            DelegateChoice {
                roleValue: Tile.Water
                Image {
                    source: "qrc:/QtExampleProject/water.png"
                }
            }
            DelegateChoice {
                roleValue: Tile.Ship
                Image {
                    source: "qrc:/QtExampleProject/ship.png"
                }
            }
            DelegateChoice {
                roleValue: Tile.Mine
                Image {
                    source: "qrc:/QtExampleProject/mine.png"
                }
            }
        }
    }
}
