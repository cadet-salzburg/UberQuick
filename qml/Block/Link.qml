import QtQuick 2.0
import UberComponents 1.0
Bezier {
    id: line
    smooth: true
    property point start
    property point end
    signal linkMoved()
    onLinkMoved:
    {
        p1 = object.getStartPos();
        updateControlPoints();
    }
    color:      "#454545"
    p1:         object.getStartPos()
    p2:         Qt.point(0, 0)
    p3:         Qt.point(0, 0)
    p4:         Qt.point(120,80);

    Component.onCompleted:
    {
        updateControlPoints();
        object.linkChanged.connect(line.linkMoved);
    }

    function updateControlPoints()
    {
        var dist = p4.x - p1.x;
        var offset = 0.5*dist;
        p2 = Qt.point(p1.x + offset, p1.y);
        p3 = Qt.point(p4.x - offset, p4.y);
    }
}
