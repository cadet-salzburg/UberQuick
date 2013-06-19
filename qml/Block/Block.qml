import QtQuick 2.0
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

    property string type: "block"
    signal          blockMoved();
    function        initialize()
    {
        var numInlets = inlets.count();
        for ( var i=0; i < numInlets; i++ )
        {
            var inlet = inlets.childAt(i);
            block.blockMoved.connect( inlet.moved );
            inlet.updatePosition();
        }
        var numOutlets = outlets.count()
        for ( var j=0; j < numOutlets; j++ )
        {
            var outlet = outlets.childAt(j);
            block.blockMoved.connect( outlet.moved );
            outlet.updatePosition();
        }
    }
    MouseArea {
        id: mouseArea
        property variant previousPosition
        onPressed: {
            previousPosition = Qt.point(mouseX, mouseY)
            workbench.state = "hideDock"
        }
        onPositionChanged: {
            if (pressedButtons === Qt.LeftButton) {
                var dx = mouseX - previousPosition.x
                var dy = mouseY - previousPosition.y
                block.parent.x += dx
                block.parent.y += dy
                object.position = Qt.point(block.x, block.y);
            }
            blockMoved();
        }
        anchors.fill: parent
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

    NodeRow {
        id: inlets
        x: block.border.width + block.radius
        y: block.border.width/2-8
        currentModel: object.getInletModel()
    }

    NodeRow {
        id: outlets
        x: block.border.width + block.radius
        y: block.height - block.border.width/2 - 8
        currentModel: object.getOutletModel()
    }
    Component.onCompleted:
    {
        initialize();
        console.log(object.className );
    }
}
