import QtQuick 2.1
BaseBlock {
    property alias text: input.text
    property alias textboxWidth: input.width
    TextElement {
        id: input
        width: parent.width - 2*parent.radius - 2*parent.border.width
        height: parent.height - 2*parent.border.width - 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        text: object.value
        onTextChanged: {
            object.value = text;
        }
    }
}
