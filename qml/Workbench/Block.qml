import QtQuick 2.0

Rectangle {
    id: block
    height: 30
    width: 150
    color: "#ffffff"
    radius: 12
    antialiasing: true
    border {
        color: "#969696"
        width: 3
    }
    MouseArea {
        anchors.fill: parent
        property variant previousPosition
        //propagateComposedEvents: true
        onPressed: {
            previousPosition = Qt.point(mouseX, mouseY)
            workbench.state = "hideDock"
            console.log("Block Pressed")
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
    //Inlets
    Row {
        spacing: 5
        anchors.verticalCenter: parent.top
        anchors.verticalCenterOffset: parent.border.width/2
        anchors.horizontalCenterOffset: parent.border.width/2
        anchors.left: parent.left
        anchors.leftMargin: parent.border.width + parent.radius
        Repeater {
            id: inlets
            model: object.getInletModel()
            delegate: Inlet {}
        }
    }
    //Outlets
    Row {
        spacing: 5
        anchors.verticalCenter: parent.bottom
        anchors.verticalCenterOffset: -parent.border.width/2
        anchors.horizontalCenterOffset: parent.border.width/2
        anchors.left: parent.left
        anchors.leftMargin: parent.border.width + parent.radius
        Repeater {
            id: outlets
            model: object.getOutletModel()
            delegate: Inlet {}
        }
    }

    Text {
        id: info
        text: object.name
        font.family: "Helvetica"
        font.pointSize: 8
        color: "dimgray"
        anchors.horizontalCenter: block.horizontalCenter
        anchors.verticalCenter: block.verticalCenter
    }
}
