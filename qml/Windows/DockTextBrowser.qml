import QtQuick 2.1
import "../Canvas"

import QtQuick 2.1

ObjectFrame {
    x: 0
    y: 0
    TextElement
    {
        id: textedit
        width: parent.width - 2*parent.radius - 2*parent.border.width
        height: parent.height - 2*parent.border.width - 2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
    Rectangle {
        id: rr
        color: "white"
        width: textedit.width
        height: 50
        anchors.top: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 2
        Component {
            id: textBrowserDelegate
            Item {
                id: item
                width: textedit.width; height: 20
                Text {
                    //text: object.string
                    text: name
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
            model: DockModel
            anchors.verticalCenter:  rr.verticalCenter
            anchors.horizontalCenter: rr.horizontalCenter
            anchors.leftMargin: 8
            anchors.rightMargin: 8
            anchors.topMargin: 8
            anchors.bottomMargin: 8
            height: count*20
            width:  textedit.textboxWidth
            delegate: textBrowserDelegate
            highlight: Rectangle { color: "#11AAAAAA" }
            focus: true
        }
    }
}
