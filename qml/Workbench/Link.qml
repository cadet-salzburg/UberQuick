import QtQuick 2.0
import UberComponents 1.0
Bezier {
    width: workbench.width
    height: workbench.height
    id: line
    color: "#454545"
    property real t: 0
    p1: object.getStartPos()
    p2: Qt.point(0, 200)
    p3: Qt.point(300 - 300*t, t*200)
    p4: Qt.point(120,80);
}
