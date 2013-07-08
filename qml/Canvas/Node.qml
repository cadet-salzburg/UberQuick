import QtQuick 2.1
import UberComponents 1.0

Circle {
    id: node
    radius: 8
    color: "#00FFFF00"
    property point  centerPoint: Qt.point(0,0)
    property point  offset: Qt.point(0,0)
    property string type: "circle"
    property real   thickness: 3
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
        var nodeCenterInWorkbench  = node.mapToItem(workbench, nodeCenter.x, nodeCenter.y );
        object.x = nodeCenterInWorkbench.x;
        object.y = nodeCenterInWorkbench.y;
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onPressed:
        {
            var pos = node.mapToItem(workbench, mouseX, mouseY );
            ConnectionManager.beginLink(object, Qt.point(pos.x, pos.y));
        }

        onPositionChanged:
        {

        }

        onReleased:
        {

        }

        DropArea {
            id: dropArea;
            anchors.fill: parent;
            onEntered: {
                drag.accept (Qt.CopyAction);
                console.log("onEntered");
            }
            onDropped: {
                drop.accept();
                console.log ("onDropped");
                ConnectionManager.finishLink(object);
                customContext.model = ConnectionManager.getConnectionOptions();
                print( customContext.model.count + "-------------");
                if ( customContext.model.count > 0 )
                {
                    customContext.popup();
                }
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
        height: node.thickness
        y: parent.height /2 - height/2
        color: "#8F8F8F"
    }

    Component.onCompleted:
    {
        node.moved.connect( object.positionChanged );
    }
}
