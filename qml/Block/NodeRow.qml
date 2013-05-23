import QtQuick 2.0
Row {
    id: row
    property variant currentModel
    property string type: "inRow"

    function count()
    {
        return repeater.count;
    }
    function childAt(idx)
    {
        return repeater.itemAt(idx);
    }

    spacing: 5


    Repeater {
        id: repeater
        property string type: "repeater"
        model: currentModel
        delegate: Node{}
    }

}
