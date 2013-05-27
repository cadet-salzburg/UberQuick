import QtQuick 2.0
import UberComponents 1.0

Circle {
    id: node
    property point  centerPoint: Qt.point(0,0)
    property point  offset: Qt.point(0,0)
    property string type: "circle"
    signal moved;
    onMoved: {
        updatePosition();
    }
    radius: 8
    color: "#00FFFF00"
    anchors.verticalCenter: parent.verticalCenter

    function printPoint( point , message )
    {
        console.log( message + " is: [" + point.x + "," + point.y + "]" );
    }

    function updatePosition()
    {
        var nodeCenter = Qt.point(node.radius, node.radius);
        printPoint(nodeCenter, "----- nodeCenter")
        var nodeCenterInWorkbench  = node.mapToItem(workbench, nodeCenter.x, nodeCenter.y );
        printPoint(nodeCenterInWorkbench, "nodeCenterInWorkbench");
        object.x = nodeCenterInWorkbench.x;
        object.y = nodeCenterInWorkbench.y;
    }
    MouseArea {
        onPressed: {
            mouse.accepted = false;
            System.beginAddingLink(object);
        }
        anchors.fill: parent
    }
    Rectangle {
        id: rect
        width: parent.width
        height: block.border.width
        y: parent.y + parent.height /2 - height/2
        color: "#8F8F8F"
    }


    Component.onCompleted:
    {
        node.moved.connect( object.positionChanged );
    }
}