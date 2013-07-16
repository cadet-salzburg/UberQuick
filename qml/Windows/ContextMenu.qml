import QtQuick 2.1
Rectangle {
    id: contextMenu
    property alias model : list.model
    height: 180
    width: 96
    radius: 6
    color:          "#FFFCFCFC"
    border.color:   "#FFDFDFDF"
    opacity: 0
    signal hide
    state: "hidden"
    states:  [
        State {
            name: "visible"
            PropertyChanges {target: contextMenu; opacity: 1; enabled: true}
        },
        State {
            name: "hidden"
            PropertyChanges {target:contextMenu; opacity: 0; enabled: false}
        }
    ]
    transitions: [
        Transition {
            from: "hidden"; to: "visible"
            NumberAnimation {
                target:  contextMenu
                properties: "opacity"
                duration: 200
            }
        },
        Transition {
            from: "visible"; to: "hidden"
            NumberAnimation {
                target:  contextMenu
                properties: "opacity"
                duration: 50
            }
        }
    ]

    Component {
        id: contextMenuDelegate
        Item {
            id: item
            width: 80; height: 20
            Text {
                text: object.string
                font.family: "Helvetica"
                font.pointSize: 8
                color: "dimgray"
            }
            MouseArea {
                onPressed: {
                    print("Item pressed:  " + index  );
                    list.currentIndex = index;
                    hide();
                }
                onEntered: {
                    list.currentIndex = index;
                }
                anchors.fill: parent
                hoverEnabled: true
            }
        }
    }

    ListView {
        id: list
        anchors.verticalCenter:  contextMenu.verticalCenter
        anchors.horizontalCenter: contextMenu.horizontalCenter
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 8
        anchors.bottomMargin: 8
        height: count*20
        width:  80
        delegate: contextMenuDelegate
        highlight: Rectangle { color: "#11AAAAAA" }
        focus: true
    }

    function popup( p )
    {
        contextMenu.x = p.x;
        contextMenu.y = p.y;
        contextMenu.height = list.height + 2*contextMenu.radius
        contextMenu.state = "visible";
    }

    onHide:
    {
        contextMenu.state = "hidden";
    }
}
