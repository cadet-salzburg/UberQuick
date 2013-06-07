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
        console.log("-----------------------0000000000000000000-----------------")
    }

    width:      workbench.width
    height:     workbench.height
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
        var dist = p4.x() - p1.x();
        var offset = dist/2;
        p2 = p1 + Qt.point( offset, 0);
        p3 = p4   - Qt.point(offset, 0);
    }
}
