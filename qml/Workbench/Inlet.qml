import QtQuick 2.0
Rectangle {
    id: node
    width: 12
    height: 12
    radius: width
    color: "#002F4F4F"
    anchors.verticalCenter: parent.verticalCenter
    MouseArea
    {
        cursorShape: Qt.PointingHandCursor
        anchors.fill: parent
        onPressed: {
            console.log(object.getName() + " pressed");
        }
    }
    Rectangle {
        width: parent.width
        height: block.border.width
        y: parent.y + parent.height /2 - height/2
        color: "#8F8F8F"
        //color: "#FFFFFF"
    }
}
