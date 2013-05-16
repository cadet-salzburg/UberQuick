import QtQuick 2.0
import UberComponents 1.0

Node {
    id: node
    radius: 8
    color: "#00FFFF00"
    anchors.verticalCenter: parent.verticalCenter
    property point actualPosition: Qt.point(0,0)

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
            //object.position =  getSceneCoords(workbench, actualPosition);
            System.beginAddingLink(object);
        }
    }
    Component.onCompleted:
    {
        actualPosition = Qt.point(node.x, node.y);
        console.log("The psi was: " + actualPosition.x + ":::" + actualPosition.y )
        var currentPos = Qt.point(0,0);
        currentPos.y = node.y;
        for ( var i=0; i< index + 1; i++ )
        {
            currentPos.x += ( parent.children[i].width + parent.spacing);
            console.log("Width is: " + parent.children[i].width );
        }
        actualPosition = currentPos;
        actualPosition.x += (width+block.border.width/2);
        actualPosition.y += ( height + block.border.width/2);
        object.position =  getSceneCoords(workbench, actualPosition);
    }
}
