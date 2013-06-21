import QtQuick 2.0

BaseBlock {
    Rectangle {
        property alias text: input.text
        id: textEditFrame
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 2*parent.radius - 2*parent.border.width
        height: parent.height - 2*parent.border.width - 2
        color: "#66EFEFEF"
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
}
