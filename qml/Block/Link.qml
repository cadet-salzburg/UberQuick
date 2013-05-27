import QtQuick 2.0
import UberComponents 1.0
Bezier {
    id: line
    property real t: 0
    signal linkMoved()
    onLinkMoved:
    {
        p1 = object.getStartPos();
    }

    width:      workbench.width
    height:     workbench.height
    color:      "#454545"
    p1:         object.getStartPos()
    p2:         Qt.point(0, 200)
    p3:         Qt.point(300 - 300*t, t*200)
    p4:         Qt.point(120,80);
    Component.onCompleted:
    {
        object.linkChanged.connect(line.linkMoved);
    }
}
