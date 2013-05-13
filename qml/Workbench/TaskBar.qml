import QtQuick 2.0
import "../UI"                  // included for button / file dialog etc
//import LogicComponents 1.0      // included for fileloader class
// fioleloader now became a context property...

Rectangle
{

    // used for loading. let's see if it should be used for saving, too?
    FileDialog
    {
        id: loadDialog

        onAccepted:
        {
            console.log( "file : " + itemToBeLoaded )
            console.log( "folder: " + currentFolder )
            if ( isValidItem ) cpFileLoader.loadFile( currentFolder + itemToBeLoaded );
            // reset the selection
            reset();
        }

    }

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
            iconPath:                   "../../Images/loadIcon.png"
            height:                     parent.height - 8
            width:                      parent.height - 8
            anchors.verticalCenter:     parent.verticalCenter
            onButtonClicked:
            {
                // set properties & show file dialog
                loadDialog.openFolder = ".";
                loadDialog.showParentDirectories = true;
                loadDialog.fileFilters = [ "*.ubef", "*.fbef" ];
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
