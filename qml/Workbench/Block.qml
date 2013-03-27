import QtQuick 2.0
Rectangle {
    id: block
    height: 30
    width: 3.625*height
    color: "#ffffff"
    radius: 12
    antialiasing: true
    border {
        color: "#969696"
        width: 3
    }

    Text {
        id: info
        text: name
        font.family: "Helvetica"
        font.pointSize: 12
        color: "dimgray"
        anchors.horizontalCenter: block.horizontalCenter
        anchors.verticalCenter: block.verticalCenter
    }
    MouseArea {
        anchors.fill: block
        property variant previousPosition
        //propagateComposedEvents: true
        onPressed: {
            console.debug("Pressed2")
            previousPosition = Qt.point(mouseX, mouseY)
            workbench.state = "hideDock"
            //mouse.accepted = false
        }
        onPositionChanged: {
            if (pressedButtons == Qt.LeftButton) {
                var dx = mouseX - previousPosition.x
                var dy = mouseY - previousPosition.y
                block.x += dx
                block.y += dy
            }
        }
    }
}
