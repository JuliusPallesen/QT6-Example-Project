import QtQuick 2.0

Rectangle {
    id: background
    color: "grey"
    width: 640
    height: 480

    Text {
        x : 25
        y : 25
        height: parent.height - 50
        width: parent.height - 50
        text : "Hello World!"
        font.bold: true
    }

    Rectangle {
        x : background.x
        y : background.y + background.height / 2
        color : "red"
        width : parent.width
        height : parent.height - y
    }
}
