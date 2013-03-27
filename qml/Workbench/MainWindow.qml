import QtQuick 2.0

Rectangle {
    id: workbench
    width: 100
    height: 62
    color: "#e6e6e6ff"
    state: "hideDock"
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        //propagateComposedEvents: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onPressed: {
            //mouse.accepted = false;
            console.debug("Pressed");
            if ( workbench.state == "showDock")
            {
                workbench.state = "hideDock"
            }
        }


        onDoubleClicked: {
            if (mouse.button == Qt.LeftButton)
            {
                var pos =_system.maptoGlobal(parent)
                _dockView.setX(pos.x+mouseX-_dockView.width/2)
                 _dockView.setY(pos.y+mouseY)
                workbench.state = "showDock"
            }
        }
    }
    Repeater {
        id: grid
        anchors.fill: parent
        model: _flowmodel;
        delegate: Item {
            id: multidel

            : console.log(display)
            Loader {
                id: loader
                source: _complexDelegate.getDelegate(object.className())
            }
        }
    }
    //------------ Custom Delegate Test Ends ----------------//

    Text {
        id: info
        text: "Double-click to make a new object"
        font.family: "Helvetica"
        font.pointSize: 24
        color: "dimgray"
        anchors.horizontalCenter: workbench.horizontalCenter
        anchors.verticalCenter: workbench.verticalCenter
    }
    TaskBar {
        anchors.bottom : workbench.bottom
    }
    states: [
        State {
            name: "hideDock"
            PropertyChanges { target: info; opacity: 1 }
            PropertyChanges { target: _dockView; visible: false }
            //_dockView.setVisible: false
        },
        State {
            name: "showDock"
            PropertyChanges { target: info; opacity: 0 }
            PropertyChanges { target: _dockView; visible: true }
           // PropertyChanges { target: _dockView; x: 100; y: 100 }
        }
    ]
}
