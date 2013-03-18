import QtQuick 2.0

Rectangle {
    id: workbench
    width: 100
    height: 62
    color: "#e6e6e6ff"
    state: "start"

    //------------ Custom Delegate Test Starts  ----------------//

//    Component {
//        id: fruitDelegate
//        Row {
//                id: fruit
//                Text { text: " Fruit: " + name; color: fruit.ListView.view.fruit_color }
//                Text { text: " Cost: $" + cost }
//                Text { text: " Language: " + fruit.ListView.view.model.language }
//        }
//    }
    ListView {
        id: grid
        anchors.fill: parent
        spacing: 2
        model: _flowmodel;
        delegate: Item {
            id: multidel
            Loader {
                id: loader
                //source: _complexDelegate.getDelegate("Uber::Inlet")\
                source: _complexDelegate.getDelegate(modeltype)
            }
        }
//            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
    }
    //------------ Custom Delegate Test Ends ----------------//

    Text {
        id: info
        text: "Double-click to make a new object"
        font.family: "Helvetica"
        font.pointSize: 24
        color: "dimgray"
        anchors.horizontalCenter: workbench.horizontalCenter
        anchors.verticalCenter: workbench.verticalCenter
    }
    TaskBar {
        anchors.bottom : workbench.bottom
    }
    states: [
        State {
            name: "start"
            PropertyChanges { target: info; opacity: 1 }
            PropertyChanges { target: _dockView; visible: false }
            //_dockView.setVisible: false
        },
        State {
            name: "showDock"
            PropertyChanges { target: info; opacity: 0 }
            PropertyChanges { target: _dockView; visible: true }
            PropertyChanges { target: _dockView; x: 100; y: 100 }


        }
    ]
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onDoubleClicked: {
            if (mouse.button == Qt.LeftButton)
            {
                workbench.state = "showDock"
            }
        }
    }

}
