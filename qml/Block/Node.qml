import QtQuick 2.0
import UberComponents 1.0

Circle {
    id: node
    property point  centerPoint: Qt.point(0,0)
    property point  offset: Qt.point(0,0)
    property string type: "circle"
    signal moved;
    //onMoved: console.log( type + " reports that it moved.");

    radius: 8
    color: "#FFFFFF00"
    anchors.verticalCenter: parent.verticalCenter
    function debugPrint( p , s)
    {
        console.log( s+" is: [" + p.x + "," + p.y + "]" );
        console.log("The width of the node is: " + node.width + " and the radius is: " + node.radius + " and the width of the rect is: " + rect.width );
    }

    Rectangle {
        id: rect
        width: parent.width
        height: block.border.width
        y: parent.y + parent.height /2 - height/2
        color: "#8F8F8F"
    }

    MouseArea {
        onPressed: {
            mouse.accepted = false;
            var rectCenter = Qt.point(rect.width/2, rect.height/2);
            debugPrint(rectCenter, "rectCenter");
            var rectCenterInNode = rect.mapToItem(node, rectCenter.x, rectCenter.y);
            debugPrint(rectCenterInNode, "rectCenterInNode");
            var rectCenterInBlock = rect.mapToItem(block,rectCenter.x, rectCenter.y );
            debugPrint(rectCenterInBlock, "rectCenterInBlock");
            var rectCenterInWorkbench = rect.mapToItem(workbench,rectCenter.x, rectCenter.y );
            debugPrint(rectCenterInWorkbench, "rectCenterInWorkbench");
            object.x = rectCenterInWorkbench.x;
            object.y = rectCenterInWorkbench.y;
            System.beginAddingLink(object);
        }
        anchors.fill: parent
    }

    Component.onCompleted:
    {
        //centerPoint = Qt.point(node.x,node.y);
        //centerPoint = Qt.point(node.x+node.radius,node.y+node.radius);
    }
}
