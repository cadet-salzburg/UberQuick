import QtQuick 2.0
Rectangle {
    id: button
    color: Qt.rgba(51./255., 51./255., 51./255.,1.0 )
    radius: 6
    antialiasing: true
    Image {
        id: button_icon
        source: path
        anchors.horizontalCenter: button.horizontalCenter
        anchors.verticalCenter: button.verticalCenter
        fillMode: Image.PreserveAspectFit
        opacity: 1.0
        width: parent.width - parent.radius
        height: parent.height - parent.radius
    }
    MouseArea {
        cursorShape: Qt.PointingHandCursor
        anchors.fill: parent
        onClicked:
        {
            Qt.quit();
        }
    }
    property alias iconPath: button_icon.source
    property alias imageWidth: button_icon.width
    property alias imageHeight: button_icon.height
}
