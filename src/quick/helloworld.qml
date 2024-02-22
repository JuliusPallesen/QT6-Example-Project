import QtQuick 2.0

Rectangle {
    id: sky
    color: "lightblue"
    width: 640
    height: 480

    Text {
        x: 25
        y: 25
        height: (parent.height - 50)
        width: (parent.height - 50)
        text: "Hello World!"
        font.bold: true
    }

    Rectangle {
        id: grass
        x: parent.x
        y: (parent.y + (parent.height / 2))
        color: "green"
        width: parent.width
        height: (parent.height - y)

        Image {
            source: "./zühlke_logo.png"
            width: 100
            height: 100
            x: parent.width - width
            y: parent.height - height
        }
    }

    Item {
        id: sun
        x: (sky.width - 100)
        y: 100

        Rectangle {
            id: sunBody
            width: 50
            height: 50
            color: "yellow"
            radius: (width / 2)
        }

        Rectangle {
            width: 5
            height: 30
            color: "yellow"
        }
    }
}
