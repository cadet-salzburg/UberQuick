import QtQuick 2.1
import QtQuick.Controls 1.0
import UberComponents 1.0
import "../Canvas"

GraphCanvas {
    id: workbench
    width: 100
    height: 62
    z: -2
    color: "#EEEEEE"
    state: "initState"
    readonly property alias mouseX: mouseArea.mouseX
    readonly property alias mouseY: mouseArea.mouseY

    ContextMenu {
        id: contextMenu
        z: 20
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        propagateComposedEvents: true
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton
        onClicked: {
            print(mouse.button);
            if (mouse.button == Qt.LeftButton) {
                if (workbench.state == "showDock") {
                    workbench.state = "hideDock"
                }
            }
        }
        onDoubleClicked: {
            if (mouse.button == Qt.LeftButton) {
                mouse.accepted = true
                var pos = System.maptoGlobal(parent)
                DockView.setX(pos.x + mouseX - DockView.width / 2)
                DockView.setY(pos.y + mouseY)

                workbench.state = "showDock"
            }
        }

        Component.onCompleted: {
            workbench.state = "startState"
            mouseArea.onClicked.connect(contextMenu.hide);
        }
    }
    Text {
        id: info
        text: "Double-click to make a new object"
        font.family: "Helvetica"
        font.pointSize: 24
        color: "dimgray"
        anchors.horizontalCenter: workbench.horizontalCenter
        anchors.verticalCenter: workbench.verticalCenter
    }

    Repeater {
        id: grid
        model: ItemModel
        delegate: Loader {
            source: ComplexDelegate.getDelegate(object.className)
        }
    }

    TaskBar {
        anchors.bottom: workbench.bottom
    }

    states: [
        State {
            name: "startState"
            PropertyChanges {
                target: info
                opacity: 1
            }
            PropertyChanges {
                target: DockView
                visible: false
            }
        },
        State {
            name: "initState"
            PropertyChanges {
                target: info
                opacity: 1
            }
            PropertyChanges {
                target: DockView
                visible: false
            }
        },
        State {
            name: "hideDock"
            PropertyChanges {
                target: info
                opacity: 0
            }
            PropertyChanges {
                target: DockView
                visible: false
            }
        },
        State {
            name: "showDock"
            PropertyChanges {
                target: info
                opacity: 0
            }
            PropertyChanges {
                target: DockView
                visible: true
            }
        }
    ]
}
