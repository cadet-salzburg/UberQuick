  import QtQuick 2.0
import "../UI"
Item {
    id: window
    Rectangle {
        id: dot
        width: 8
        height: width
        border.color: Qt.rgba(0.6,0.6,0.6,1.)
        color: Qt.rgba(0.15,0.15,0.15,0.)
        radius: width/2
        border.width: 1
        antialiasing: true
        anchors.horizontalCenter: parent.horizontalCenter
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.OpenHandCursor
            property variant previousPosition
            onPressed: {
                //cursorShape: Qt.ClosedHandCursor
                previousPosition = Qt.point(mouseX, mouseY)
            }
            onPositionChanged: {
                //cursorShape: Qt.ClosedHandCursor
                if (pressedButtons == Qt.LeftButton) {
                    var dx = mouseX - previousPosition.x
                    var dy = mouseY - previousPosition.y
                    DockView.x = DockView.x + dx
                    DockView.y = DockView.y + dy
                }
            }
        }
    }
    Rectangle {
        id: dock
        width: parent.width
        height: parent.height - dot.height - 5
        color:  Qt.rgba(0.8,0.8,0.8,0.9)
        radius: 15
        border.color: dot.border.color
        border.width: dot.border.width
        antialiasing: true
        anchors.top: dot.bottom
        anchors.topMargin: 5

        Component {
            id: dockDelegate
            Item {
                width: grid.cellWidth - 5; height: grid.cellHeight - 5
                //anchors.margins: 10
                Image {
                    anchors.fill: parent
                    source: path;
                    anchors.horizontalCenter: parent.horizontalCenter
//                    fillMode: Image.PreserveAspectFit
                    MouseArea {
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                        onClicked: {
                            System.addBlock(index, Qt.point(mouseX, mouseY))
                            //_system.
                           // _system.
//                            Qt.quit();
                        }
                    }
                }
            }
        }
        GridView {
            id: grid
            anchors.fill: parent
            anchors.margins: parent.radius
            cellWidth: 40; cellHeight: 40
            model: DockModel;
            delegate: dockDelegate
//            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            MouseArea {
                onClicked: {
                    window.state = "hideDock"
                }
            }
        }
        Button {
            iconPath:"../../Images/handleAIcon.png"
            width: 22
            height: 22
            color: Qt.rgba(51./255., 51./255., 51./255.,0.0 )
            anchors.right: dock.right
            anchors.bottom: dock.bottom
            anchors.margins: 3

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.SizeFDiagCursor
                property variant previousPosition
                onPressed: {
                    previousPosition = Qt.point(mouseX, mouseY)
                }
                onPositionChanged: {
                    //previousPosition = Qt.point(mouseX, mouseY)
                    if (pressedButtons == Qt.LeftButton) {
                        var dx = mouseX - previousPosition.x
                        var dy = mouseY - previousPosition.y
                        DockView.width = DockView.width + dx
                        DockView.height = DockView.height + dy
                    }
                }
            }
        }
    }
}
