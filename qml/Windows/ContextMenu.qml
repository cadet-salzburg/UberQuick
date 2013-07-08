import QtQuick 2.1
import QtQuick.Controls 1.0

Menu {
    id: contextMenu
    property alias model: inst.model
    property int selectionIndex: -1
    visible: true
    Instantiator {
        id: inst
        delegate:
        MenuItem {
            text: modelData.string;
            onTriggered: {
                print("MenuItem triggered")
                contextMenu.selectionIndex = index;
            }
            onVisibleChanged:
            {
                print("Visibility changed")
            }

            onToggled: {
                print("Whatever toggle means")
            }
        }
        onObjectAdded: contextMenu.insertItem(index,object)
        onObjectRemoved: contextMenu.removeItem(object)
    }
    onPopupVisibleChanged: {
        print("Popup Visible Changed")
    }
}
