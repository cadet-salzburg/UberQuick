import QtQuick 2.1
Rectangle {
    id: textEditFrame
    property alias text : input.text
    color: "#66EFEFEF"
    border.width: 0
    TextInput {
        id: input
        selectionColor: "green"
        font.family: "Helvetica"
        font.pointSize: 8
        color: "dimgray"
        width: parent.width-16
        maximumLength: 14
        anchors.centerIn: parent
        //focus: true
    }
}
