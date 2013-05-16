import QtQuick 2.0
import UberComponents 1.0
Rectangle {
        id: block
        height: 30
        width: 150
        color: "#FFFCFCFC"
        radius: 12
        x: object.position.x
        y: object.position.y
        z: 0
        antialiasing: true
        border {
            color: "#FFAFAFAF"
            width: 3
        }
        signal updateIoRegions();
        MouseArea {
            anchors.fill: parent
            property variant previousPosition
            //propagateComposedEvents: true
            onPressed: {
                previousPosition = Qt.point(mouseX, mouseY)
                workbench.state = "hideDock"
                //console.log("Block Pressed")
                //mouse.accepted = false
            }
            onPositionChanged: {
                if (pressedButtons === Qt.LeftButton) {
                    var dx = mouseX - previousPosition.x
                    var dy = mouseY - previousPosition.y
                    block.x += dx
                    block.y += dy
                    object.position = Qt.point(block.x, block.y);
                }
                emit
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
            enabled: false;
        }
    //Inlets
        Row {
            id: inletRow
            spacing: 5
            anchors.verticalCenter: block.top
            anchors.verticalCenterOffset: block.border.width/2
            anchors.horizontalCenterOffset: block.border.width/2
            anchors.left: block.left
            anchors.leftMargin: block.border.width + block.radius
            Repeater {
                id: repeater
                model: object.getInletModel()
                delegate: Inlet {}
                onItemAdded:
                {
                    //console.log( item.x +"---"+ item.y )
                }
            }
        }
        //Outlets
        Row {
            id: outletRow
            spacing: 5
            anchors.verticalCenter: block.bottom
            anchors.verticalCenterOffset: -block.border.width/2
            anchors.horizontalCenterOffset: block.border.width/2
            anchors.left: block.left
            anchors.leftMargin: block.border.width + block.radius
            Repeater {
                model: object.getOutletModel()
                delegate: Inlet {}
            }
        }
}
