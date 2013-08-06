import QtQuick 2.1
import UberComponents 1.0
import "../../js/Bezier.js" as UberJS
//Bezier {
//    id: line
//    smooth: true
//    z: -100
//    fillColor: "#8F8F8F"
//    outlineColor: "#555555"
//    signal linkMoved()
//    onLinkMoved:
//    {
//        //console.log("onLinkMoved");
//        p1 = object.getStartPos();
//        p4 = object.getEndPos();
//        updateControlPoints();
//    }

//    Component.onCompleted:
//    {
//        p1 = object.getStartPos();
//        p4 = object.getEndPos();
//        updateControlPoints();
//        object.linkChanged.connect(line.linkMoved);
//        console.log("Start: " + p1 + " end: " + p4);
//    }

//    function updateControlPoints()
//    {
//        var dist = p4.y - p1.y;
//        var offset = 0.5*dist;
//        p2 = Qt.point(p1.x, p1.y + offset );
//        p3 = Qt.point(p4.x, p4.y - offset );
//    }
//}

Canvas {
    id: line
    smooth: false
    antialiasing: true
    renderTarget: Canvas.FramebufferObject
    property point p1
    property point p2
    property int r: 255
    property int g: 0
    property int b: 0
    property rect rectangle;
    property point cp1
    property point cp2
    property int boundary: 20;
    property var bezier;
    signal linkMoved()
    property color selectedColor: "#FF4545"
    property color unselectedColor: "#454545"
    property bool selected: false;
    property var ctx: line.getContext('2d');
    onPaint: {
        ctx.strokeStyle = selected ? selectedColor : unselectedColor;
        ctx.lineWidth = 3;
        ctx.beginPath();
        ctx.moveTo(bezier.start.x , bezier.start.y);
        ctx.bezierCurveTo(bezier.cpStart.x , bezier.cpStart.y, bezier.cpEnd.x , bezier.cpEnd.y, bezier.end.x , bezier.end.y);
        ctx.stroke();
        ctx.closePath();
    }

    onLinkMoved:
    {
        bezier.update(object.getStartPos(), object.getEndPos(), boundary);
        var pos = bezier.getCanvasPosition();
        line.x =pos.x;
        line.y = pos.y;
        line.width = bezier.getCanvasWidth();
        line.height = bezier.getCanvasHeight();
        markDirty(Qt.rect(line.x,line.y,line.width,line.height));
        //update();
    }

    Component.onCompleted:
    {
        bezier = new UberJS.Bezier(p1,p2,boundary);
        object.linkChanged.connect(line.linkMoved);
        //console.log("Start: " + p1 + " end: " + p4);
    }
    MouseArea {
        // Returns true if we click on the curve
        function intersectPath(mouseX, mouseY, margin)
        {
            for(var x = mouseX - margin; x< mouseX + margin; x++)
            {
                for(var y = mouseY - margin; y< mouseY + margin; y++)
                {
                    if( line.ctx.isPointInPath(x, y) )
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        anchors.fill: parent
        hoverEnabled: true

        //Propagate the event to the connections below
        onPressed: {
            var accept = intersectPath(mouseX, mouseY, 2);
            line.selected = accept;
            mouse.accepted = accept;
            line.requestPaint();
        }
        onClicked: {
            if ( intersectPath(mouseX, mouseY, 2) )
            {
                System.removeItem(object);
            }

        }
        onPositionChanged: {
            var accept = intersectPath(mouseX, mouseY, 2);
            line.selected = accept;
            mouse.accepted = accept;
            line.requestPaint();
        }
    }
}
