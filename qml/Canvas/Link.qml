import QtQuick 2.1
import UberComponents 1.0
Bezier {
    id: line
    smooth: true
    z: -100
    property point start
    property point end
    signal linkMoved()
    onLinkMoved:
    {
        //console.log("onLinkMoved");
        p1 = object.getStartPos();
        p4 = object.getEndPos();
        updateControlPoints();
    }
    color: "#454545"

    Component.onCompleted:
    {
        p1 = object.getStartPos();
        p4 = object.getEndPos();
        updateControlPoints();
        object.linkChanged.connect(line.linkMoved);
        console.log("Start: " + p1 + " end: " + p4);
    }

    function updateControlPoints()
    {
        var dist = p4.y - p1.y;
        var offset = 0.5*dist;
        p2 = Qt.point(p1.x, p1.y + offset );
        p3 = Qt.point(p4.x, p4.y - offset );
    }
//    Circle {
//        radius: 5
//        x: p1.x - radius
//        y: p1.y - radius
//        color: "#ff0000"
//    }
//    Circle {
//        radius: 5
//        x: p4.x - radius
//        y: p4.y - radius
//        color: "#0000ff"
//    }
}
