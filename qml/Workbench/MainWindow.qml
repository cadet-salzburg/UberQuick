import QtQuick 2.0
//import QtDesktop 1.0
import UberComponents 1.0
import "../UI"
Canvas {
    id: workbench
    width: 100
    height: 62
    color: "#EEEEEE"
    state: "initState"
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        propagateComposedEvents: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onPressed:
        {
            if ( mouse.button == Qt.RightButton )
            {
                console.debug(getTypeOfChildAt(mouseX, mouseY));
            }
            else if ( mouse.button == Qt.LeftButton )
            {
                if ( workbench.state == "showDock")
                {
                    workbench.state = "hideDock";
                }
            }
        }

        onDoubleClicked: {
            if (mouse.button == Qt.LeftButton)
            {
                mouse.accepted = true;
                var pos = System.maptoGlobal(parent)
                DockView.setX(pos.x+mouseX-DockView.width/2)
                 DockView.setY(pos.y+mouseY)

                workbench.state = "showDock"
            }
        }
        Component.onCompleted:
        {
            DockView.visible = false;
        }
    }

    Repeater {
        id: grid
        model: ItemModel
        delegate: Loader {
            source: object.url
            x: object.position.x
            y: object.position.y
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
            name: "startState"
            PropertyChanges { target: info; opacity: 1 }
            PropertyChanges { target: DockView; visible: false }
        },
        State {
            name: "initState"
            PropertyChanges { target: info; opacity: 1 }
            PropertyChanges { target: DockView; visible: false }
        },
        State {
            name: "hideDock"
            PropertyChanges { target: info; opacity: 0 }
            PropertyChanges { target: DockView; visible: false }
        },
        State {
            name: "showDock"
            PropertyChanges { target: info; opacity: 0 }
            PropertyChanges { target: DockView; visible: true }
        }
    ]
}
