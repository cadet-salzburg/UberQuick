import QtQuick 2.1
import QtQuick.Dialogs 1.0
import "../Canvas"


Rectangle
{

// used for loading. let's see if it should be used for saving, too?
//    FileDialog {
//        id: loadDialog
//        onAccepted:
//        {
//            console.log( "file : " + itemToBeLoaded )
//            console.log( "folder: " + currentFolder )
//            if ( isValidItem ) cpFileLoader.loadFile( currentFolder + itemToBeLoaded );
//            // reset the selection
//            reset();
//        }
//    }
    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        nameFilters: [ "Ubercode format (*.ubef *.fbef)", "All files (*)" ]
        visible: false
        //modality: ApplicationModal
        onAccepted: {
            Qt.quit()
        }
        onRejected: {
            Qt.quit()
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
            iconPath:                   "qrc:///images/edit-icon.png"
            height:                     parent.height - 8
            width:                      parent.height - 8
            anchors.verticalCenter:     parent.verticalCenter
            onButtonClicked:
            {
            }
        }
        Button
        {
            iconPath:                   "qrc:///images/view-icon.png"
            height:                     parent.height - 8
            width:                      parent.height - 8
            anchors.verticalCenter:     parent.verticalCenter
            onButtonClicked:
            {
            }
        }
        Button
        {
            iconPath:                   "qrc:///images/lock-icon.png"
            height:                     parent.height - 8
            width:                      parent.height - 8
            anchors.verticalCenter:     parent.verticalCenter
            onButtonClicked:
            {
            }
        }

        Button
        {
            iconPath:                   "qrc:///images/open-icon.png"
            height:                     parent.height - 8
            width:                      parent.height - 8
            anchors.verticalCenter:     parent.verticalCenter
            onButtonClicked:
            {
//                // set properties & show file dialog
//                loadDialog.openFolder = ".";
//                loadDialog.showParentDirectories = true;
//                loadDialog.fileFilters = [ "*.ubef", "*.fbef" ];
//                loadDialog.show()
                fileDialog.open();
            }
        }
        Button
        {
            iconPath:"qrc:///images/save-icon.png";
            height: parent.height - 8;
            width: parent.height - 8;
            anchors.verticalCenter: parent.verticalCenter
            onButtonClicked:
            {
            }
        }
    }
}
