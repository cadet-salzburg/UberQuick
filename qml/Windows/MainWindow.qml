import QtQuick 2.1
//import QtDesktop 1.0
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
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (mouse.button == Qt.RightButton) {
                console.debug(getTypeOfChildAt(mouseX, mouseY))
            } else if (mouse.button == Qt.LeftButton) {
                if (workbench.state == "showDock") {
                    workbench.state = "hideDock"
                }
            }
        }

        onPositionChanged: {
            //print("X is: " +mouseX+ "Y is: " + mouseY);
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
            //DockView.visible = false;
            mouseArea.onClicked.connect(contextMenu.hide);
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


    //    Rectangle {
    //        x: 150
    //        y: 150
    //        z: 0
    //        width: 80
    //        height: 80
    //        color: "#FF8822"
    //        DropArea {
    //            anchors.fill: parent
    //            onDropped: {
    //                drop.accept();
    //                console.log("Dropped in rectangle")
    //            }
    //        }
    //        MouseArea {
    //            anchors.fill: parent
    //            drag.axis: Drag.XAndYAxis
    //            drag.target: parent
    //        }
    //    }

    Repeater {
        id: grid
        model: ItemModel
        delegate: Loader {
            source: ComplexDelegate.getDelegate(object.className)
//            x: object.x
//            y: object.y
            onLoaded: {
                console.log("---->" + object.className)
            }
        }
    }

    DockTextBrowser {

    }







//    Menu {
//        id:  mmm
//        title: "Edit"
//        MenuItem {
//            text: "Cut"
//            shortcut: "Ctrl+X"
//        }

//        MenuItem {
//            text: "Copy"
//            shortcut: "Ctrl+C"
//        }

//        MenuItem {
//            text: "Paste"
//            shortcut: "Ctrl+V"
//        }

//        MenuSeparator { }

//        Menu {
//            title: "More Stuff"

//            MenuItem {
//                text: "Do Nothing"
//            }
//        }
//    }

    //    CanvasConnection {
    //        x1: 40
    //        y1: 40
    //        x2: 200
    //        y2: 200
    //    }
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
