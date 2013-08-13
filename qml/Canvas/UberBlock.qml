import QtQuick 2.1
//import UberComponents 1.0

BaseBlock
{
    Text {
        id: info
        text: object.objectName
        font.family: "Helvetica"
        font.pointSize: 8
        color: "dimgray"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        enabled: false;
    }
}
