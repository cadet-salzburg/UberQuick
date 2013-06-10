import QtQuick 2.0
import UberComponents 1.0

Circle {
    id: node
    radius: 8
    color: "#00FFFF00"
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

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onPressed:
        {
            //node.forceActiveFocus();
            console.log("Mouse Pressed at " + object.className );
            ConnectionManager.beginAddingLink(object);
            //ConnectionManager.updateLink(node.mapToItem(workbench, mouseX, mouseY ));
            ConnectionManager.startDrag(object);
        }
        onPositionChanged:
        {
            //console.log("PPPPPpppppposition changed" );
            //ConnectionManager.updateLink(Qt.point(mouseX, mouseY));
        }
        onReleased:
        {
            //console.debug("RRRRRRrrrrreleased");
        }

//        onReleased:
//        {
//            if ( containsMouse )
//            {
//                console.log("Mouse Released at " + object.className );
//                mouse.accepted = true;
//            } else {
//                mouse.accepted = false;
//            }

//        }
//        onEntered:
//        {
//            console.log("Mouse Entered at " + object.className );
//        }
        DropArea {
            id: dropArea;
            anchors.fill: parent;
            onEntered: {
                drag.accept (Qt.CopyAction);
                console.log("onEntered");
            }
            onDropped: {
                console.log ("onDropped");
                //ConnectionManager.finishAddingLink(object);
            }
            onExited: {
                console.log ("onExited");
            }
            onPositionChanged: {
                console.log ("onPosition changed");
            }
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
