import QtQuick 2.1
Row {
    id: row
    property variant currentModel
    property string type: "inRow"
    //property alias nodeWidth : node.width

    function count()
    {
        return repeater.count;
    }
    function childAt(idx)
    {
        return repeater.itemAt(idx);
    }
    function getNeededWidth( numNodes )
    {
        return ( numNodes*8*2 + (numNodes-1)*spacing );
    }

    spacing: 5
    Component {
        id: nodeComponent
        Node {
            id: node
            thickness: row.parent.border.width
            anchors.verticalCenter: row.verticalCenter
        }
    }

    Repeater {
        id: repeater
        property string type: "repeater"
        model: currentModel
        delegate: nodeComponent
    }
}
