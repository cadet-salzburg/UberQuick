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

    MouseArea {
        anchors.fill: block
        property variant previousPosition
        //propagateComposedEvents: true
        onPressed: {
            console.debug("Pressed2")
            previousPosition = Qt.point(mouseX, mouseY)
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
