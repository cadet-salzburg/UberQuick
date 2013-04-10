import QtQuick 2.0
import QtDesktop 1.0
import "../UI"
import LogicComponents 1.0
import Qt.labs.folderlistmodel 1.0

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
            FileLoader
            {
                id: fileLoader;
            }

            Dialog
            {
                ListView
                {
                    id:         fileView
                    width:      200
                    height:     400
                    model:      folderModel
                    delegate:   fileDelegate

                    property string listViewTestThingie: ""

                    FolderListModel
                    {
                        id: folderModel
                        //nameFilters: ["*.ubef"]
                    }

                    Component
                    {
                        id: fileDelegate
                        Rectangle
                        {
                            id: fileDisplay
                            width: 200
                            color: "white"
                            Text
                            {
                                id: fileDisplayText
                                text: fileName
                            }
                            height: fileDisplayText.height + 10
                            MouseArea
                            {
                                id: fileDisplayArea
                                anchors.fill: parent
                                onClicked:
                                {
                                    fileView.listViewTestThingie = fileDisplayText.text.toString()
                                    console.log( "clicked on " + fileDisplayText.text.toString() )
                                }
                            }
                        }
                    }
                }


                id: fileSelectDialog
                width: 500
                height: 500
                title: "PLEASE SELECT YOUR FILE, YOU MORON."

                Rectangle
                {
                    x: 10
                    y: 200
                    width: 200
                    height: 30
                    id: selectedRectangle
                    property string displayText : fileView.listViewTestThingie
                    Text
                    {
                        text: selectedRectangle.displayText
                    }
                }

                onClosed:
                {
                    console.log( "dialog closed" );
                }

                onAccepted:
                {
                    console.log( selectedRectangle.displayText )
                    console.log( "file chosen for loading" );
                    fileLoader.loadFile( selectedRectangle.displayText )
                }

                onRejected:
                {
                    console.log( "file loading cancelled" );
                }
            }

            iconPath:                   "../../Images/loadIcon.png"
            height:                     parent.height - 8
            width:                      parent.height - 8
            anchors.verticalCenter:     parent.verticalCenter
            onButtonClicked:
            {
                fileSelectDialog.show()
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
