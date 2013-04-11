import QtQuick 2.0
import "../UI"                  // included for button / file dialog etc
import LogicComponents 1.0      // included for fileloader class

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
            }
        }
        Button
        {
            iconPath:                   "../../Images/lockIcon.png"
            height:                     parent.height - 8
            width:                      parent.height - 8
            anchors.verticalCenter:     parent.verticalCenter
            onButtonClicked:
            {
            }
        }

        Button
        {
            FileLoader
            {
                id: fileLoader;
            }

            FileDialog
            {
                id: loadDialog
                onAccepted:
                {
                    if (  isValidItem ) fileLoader.loadFile( itemToBeLoaded );
                    reset();
                }

            }

            iconPath:                   "../../Images/loadIcon.png"
            height:                     parent.height - 8
            width:                      parent.height - 8
            anchors.verticalCenter:     parent.verticalCenter
            onButtonClicked:
            {
                loadDialog.show()
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
            }
        }
    }
}
