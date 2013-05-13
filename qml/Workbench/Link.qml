import QtQuick 2.0
import UberComponents 1.0
Bezier {
    width: workbench.width
    height: workbench.height
    id: line
//    property real t
//    SequentialAnimation on t {
//        NumberAnimation { to: 1; duration: 2000; easing.type: Easing.InOutQuad }
//        NumberAnimation { to: 0; duration: 2000; easing.type: Easing.InOutQuad }
//        loops: Animation.Infinite
//    }
    p1: Qt.point(0.1,0.2);
    p2: Qt.point(0, 1)
    p3: Qt.point(1 - t, t)
    p4: Qt.point(0.4,0.4);
}
