import QtQuick 2.1
import UberComponents 1.0
Rectangle {
    id:             block
    width:          150
    height:         30
    radius:         12
    color:          "#FFFCFCFC"
    border.color:   "#FFAFAFAF"
    border.width:   3
    antialiasing:   true
    z:  10000

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: parent
        onPositionChanged: {
            print(Qt.point(block.x, block.y));
        }
        onClicked: {
            workbench.state = "hideDock"
        }
    }
}
