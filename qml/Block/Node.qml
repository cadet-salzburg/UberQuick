import QtQuick 2.0
import UberComponents 1.0

Circle {
    id: node
    radius: 8
    color: "#CCFFFF00"
    anchors.verticalCenter: parent.verticalCenter
    property point  centerPoint: Qt.point(0,0)
    property point  offset: Qt.point(0,0)
    property string type: "circle"

    signal moved;
    onMoved: {
        updatePosition();
    }

    function printPoint( point , message )
    {
        console.log( message + " is: [" + point.x + "," + point.y + "]" );
    }

    function updatePosition()
    {
        var nodeCenter = Qt.point(node.radius, node.radius);
//        printPoint(nodeCenter, "----- nodeCenter")
        var nodeCenterInWorkbench  = node.mapToItem(workbench, nodeCenter.x, nodeCenter.y );
//        printPoint(nodeCenterInWorkbench, "nodeCenterInWorkbench");
        object.x = nodeCenterInWorkbench.x;
        object.y = nodeCenterInWorkbench.y;
    }

    DropArea {
        id: dropArea;
        anchors.fill: parent;
        onEntered: {
            drag.accept (Qt.CopyAction);
            console.log("onEntered");
        }
        onDropped: {
            console.log ("onDropped");
        }
        onExited: {
            console.log ("onExited");
        }
    }


    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onPressed:
        {
            console.log("Mouse Pressed at " + object.className );
            System.beginAddingLink(object);

        }
        onReleased:
        {
            if ( containsMouse )
            {
                console.log("Mouse Released at " + object.className );
                mouse.accepted = true;
            } else {
                mouse.accepted = false;
            }

        }
        onEntered:
        {
            console.log("Mouse Entered at " + object.className );
        }
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
