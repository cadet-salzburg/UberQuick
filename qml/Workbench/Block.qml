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
    //Inlets
    Row {
        x: 30
        y: 0
        spacing: 4
        Repeater {
            id: inlets
            model: object.getInletModel()
            delegate: Inlet {
                color: "#ffffff"
            }
        }
        height: 4
        anchors.left: parent.left
        anchors.leftMargin: parent.radius
    }

    Text {
        id: info
        text: object.name
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
