import QtQuick 2.1
import UberComponents 1.0

ObjectFrame {
    property string type: "block"
    x: object.x
    y: object.y
    signal          blockMoved();
    function        initialize()
    {
        var numInlets = inlets.count();
        for ( var i=0; i < numInlets; i++ )
        {
            var inlet = inlets.childAt(i);
            blockMoved.connect( inlet.moved );
            inlet.updatePosition();
        }
        var numOutlets = outlets.count()
        for ( var j=0; j < numOutlets; j++ )
        {
            var outlet = outlets.childAt(j);
            blockMoved.connect( outlet.moved );
            outlet.updatePosition();
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
        onPositionChanged:
        {
            object.position = Qt.point(parent.x, parent.y);
            blockMoved();
        }
        onClicked: {
            if ( mouse.button == Qt.RightButton )
            {
                System.removeItem(object);
            }
            workbench.state = "hideDock"
        }
    }

    NodeRow {
        id: inlets
        x: parent.border.width + parent.radius
        y: parent.border.width/2-8
        currentModel: object.getInletModel()
        Component.onCompleted: {
            var w = parent.width - 2*parent.radius - 2*parent.border.width
            if ( inlets.width > w )
            {
                parent.width = inlets.getNeededWidth( inlets.count()) + 2*parent.radius + 2*parent.border.width;
            }
        }
    }

    NodeRow {
        id: outlets
        x: parent.border.width + parent.radius
        y: parent.height - parent.border.width/2 - 8
        currentModel: object.getOutletModel()
        Component.onCompleted: {
            var w = parent.width - 2*parent.radius - 2*parent.border.width
            if ( inlets.width > w )
            {
                parent.width = outlets.getNeededWidth( outlets.count()) + 2*parent.radius + 2*parent.border.width;
            }
        }
    }
    Component.onCompleted:
    {
        initialize();
    }
}

