import QtQuick 2.1

Rectangle {
    id: contextMenu
    property alias model : list.model
    height: 180
    width: 80
    visible: false
    color:          "#FFFCFCFC"
    border.color:   "#FFAFAFAF"
    Component {
        id: contextMenuDelegate
        Item {
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
        anchors.fill: parent
        delegate: contextMenuDelegate
        highlight: Rectangle { color: "beige" }
        focus: true
    }
    function popup()
    {
        contextMenu.x = workbench.mouseX;
        contextMenu.y = workbench.mouseY;
        contextMenu.visible = true;
        //        print( model.count + "<-----------");
    }
    function hide()
    {
        contextMenu.visible = false;
    }
}
