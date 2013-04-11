import QtQuick 2.0
import QtDesktop 1.0
import Qt.labs.folderlistmodel 1.0

Dialog
{
    id:         fileDialog
    width:      500
    height:     500
    title:      "SELECT A FILE, YOU MORON"

    property alias itemToBeLoaded: selectionHolder.item
    property alias isValidItem: selectionHolder.valid
    property alias currentFolder: selectionHolder.folder

    signal reset()
    onReset:
    {
        itemToBeLoaded = "";
        isValidItem = false;
        currentFolder = "..\\";
    }

    Item
    {
        id: statesHolder
        states: [
            State {
                name: "nullSelection"; when: selectionHolder.item == ""
                PropertyChanges { target: selectionDisplay; color: "white" }
            },
            State {
                name: "folderSelection"; when: selectionHolder.item != "" && !selectionHolder.valid
                PropertyChanges { target: selectionDisplay; color: "orange" }
            },
            State {
                name: "fileSelection"; when: selectionHolder.item != "" && selectionHolder.valid
                PropertyChanges { target: selectionDisplay; color: "lightsteelblue" }
            }
        ]
    }

    Item
    {
        id: selectionHolder
        property string item:   ""
        property bool valid:    false;
        property url folder:    "..\\";
    }

    ListView
    {
        id:                 fileView
        model:              fileModel
        delegate:           fileDelegate
        width:              parent.width
        height:             parent.height - 60

        FolderListModel
        {
            id:                 fileModel
            folder:             selectionHolder.folder
            showDotAndDotDot:   true
            //nameFilters:    [ "*.ubef", "*.fbef" ]
        }

        Component
        {
            id:             fileDelegate
            Rectangle
            {
                width:      parent.width
                height:     20

                Text
                {
                    text:           fileName
                    color:          fileModel.isFolder( index ) ? "lightsteelblue" : "orange"
                }
                MouseArea
                {
                    anchors.fill:   parent
                    onClicked:
                    {
                        if ( fileModel.isFolder( index ) )
                        {
                            selectionHolder.item = "";
                            selectionHolder.valid = false;
                            fileModel.folder = fileModel.folder + "/" + fileName;
                        }
                        else
                        {
                            selectionHolder.item = fileName;
                            selectionHolder.valid = true;
                        }
                    }
                }
            }
        }
    }

    Rectangle
    {
        id:                 selectionDisplay
        anchors.left:       parent.left
        anchors.bottom:     parent.bottom
        width:              parent.width
        height:             40

        Text
        {
            anchors.centerIn: parent
            text: selectionHolder.item
        }
    }

    onClosed:
    {
    }

    onAccepted:
    {
    }

    onRejected:
    {
    }
}
