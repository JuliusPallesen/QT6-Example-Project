import QtQuick 2.0

Text {
    id: helloworldtext
    visible: true
    text: qsTr("My Text from C++: " + cppText)
    font.pointSize: 16
    style: Text.Outline
    styleColor: "white"
    font.bold: true
}
