import QtQuick 2.1
import UberComponents 1.0
BaseBlock {
    id: imageBlock
    width: 100
    height: 100
    property int minWidth: 100
    property int minHeight: 100
    ImageView {
        anchors.fill: parent
        anchors.margins: 15
        imageProvider: object
    }
    Button {
        iconPath:"qrc:///images/handle-icon.png"
        width: 16
        height: 16
        color: Qt.rgba(51./255., 51./255., 51./255.,0.0 )
        anchors.right: imageBlock.right
        anchors.bottom: imageBlock.bottom
        anchors.margins: 3

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.SizeFDiagCursor
            property variant previousPosition
            onPressed: {
                previousPosition = Qt.point(mouseX, mouseY)
            }
            onPositionChanged: {
                if (pressedButtons == Qt.LeftButton) {
                    var dx = mouseX - previousPosition.x
                    var dy = mouseY - previousPosition.y
                    var newWidth = imageBlock.width + dx
                    var newHeight = imageBlock.height + dy
                    if ( newWidth >= minWidth )
                    {
                        imageBlock.width = newWidth;
                    }
                    if ( newHeight >= minHeight )
                    {
                        imageBlock.height = newHeight;
                    }
                }
            }
        }
    }
}
