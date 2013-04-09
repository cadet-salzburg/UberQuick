import QtQuick 2.0
import "../UI"

Rectangle {
    width:      parent.width
    height:     35
    gradient:   Gradient
                {
                    GradientStop { position: -0.5; color: parent.color }
                    GradientStop { position: 0.95; color: "grey" }
                    GradientStop { position: 1.0; color: "grey" }
                }
    Row {
        spacing:                4
        height:                 parent.height
        anchors.left:           parent.left
        anchors.leftMargin:     spacing
        Button
        {
            iconPath:                   "../../Images/editIcon.png"
            height:                     parent.height - 8
            width:                      parent.height - 8
            anchors.verticalCenter:     parent.verticalCenter
            onButtonClicked:
            {
                console.log( "0" )
            }
        }
        Button
        {
            iconPath:                   "../../Images/viewIcon.png"
            height:                     parent.height - 8
            width:                      parent.height - 8
            anchors.verticalCenter:     parent.verticalCenter
            onButtonClicked:
            {
                console.log( "1" )
            }
        }
        Button
        {
            iconPath:                   "../../Images/lockIcon.png"
            height:                     parent.height - 8
            width:                      parent.height - 8;
            anchors.verticalCenter:     parent.verticalCenter
            onButtonClicked:
            {
                console.log( "2" )
            }
        }
        Button
        {
            iconPath:                   "../../Images/loadIcon.png"
            height:                     parent.height - 8
            width:                      parent.height - 8
            anchors.verticalCenter:     parent.verticalCenter
            onButtonClicked:
            {
                console.log( "3" )
            }
        }
        Button
        {
            iconPath:"../../Images/saveIcon.png";
            height: parent.height - 8;
            width: parent.height - 8;
            anchors.verticalCenter: parent.verticalCenter
            onButtonClicked:
            {
                console.log( "4" )
            }
        }
    }
}
