import QtQuick 2.0
import UberComponents 1.0
Node {
    id: node
    radius: 8
    color: "#FFFFFF00"
    anchors.verticalCenter: parent.verticalCenter
    Rectangle {
        width: parent.width
        height: block.border.width
        y: parent.y + parent.height /2 - height/2
        color: "#8F8F8F"
    }
    MouseArea {
        anchors.fill: parent
        onPressed: {
            console.log("IoNode Pressed")
            mouse.accepted = false
            System.beginAddingLink(Qt.point(mouseX,mouseY))
        }
    }
}
