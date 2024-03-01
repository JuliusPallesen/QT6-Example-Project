import QtQuick
import QtQuick.Window
import Tile
import Battlefield
import Qt.labs.qmlmodels

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("QML CPP M/V Demo")
/*
    TableView {
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1

        model: Battlefield {
            id: bf
        }

        delegate: Image {
            height: 100
            width: 100
            source: {
                console.log("Index: ", index.row, index.column);
                console.log("Model data: ", modelData);
                console.log("Model: ", model);
                var tile = bf.data();
                if (model !== null) {
                    switch (model.tile_type) {
                    case Tile.Water:
                        return "qrc:/QtExampleProject/water.png";
                    case Tile.Ship:
                        return "qrc:/QtExampleProject/ship.png";
                    case Tile.Mine:
                        return "qrc:/QtExampleProject/mine.png";
                    default:
                        return "";
                    }
                } else {
                    return "";
                }
            }
        }
    }
*/
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
