var menuWidth = -1;
var rowHeight = -1;
var docRoot = null;
var docRootWidth = -1;
var menuPadding = 64;

function getDocRoot()
{
    if(!docRoot)
    {
    docRoot = menuRoot.parent;

    while(docRoot.parent)
    {
        docRoot = docRoot.parent;
    }
    }
    return docRoot;
}

function getMenuWidth()
{
    if(menuWidth == -1 || (getDocRoot().width != docRootWidth))
    {
        docRootWidth = getDocRoot().width;
        for( var i = 0; i < model.count; i++ )
        {
            //var textItem = Qt.createQmlObject('import Qt 2.0; Item { Text { font.pointSize: 12; text: "something" }}', menuList );
//            var textItem = Qt.createQmlObject('import Qt 2.0; Text { font.pointSize:' + 112 + '; text: "' + "some" + '"}',
//            menuList, "dynamicSnippet1");

            //var textItem = Qt.createQmlObject('import QtQuick 2.0; Rectangle {color: "red"; width: 20; height: 20}', menuList);
            var textItem = Qt.createQmlObject('import QtQuick 2.0; Text { font.pointSize: 12; text: "something" }', menuList);


            menuWidth = Math.max(menuWidth, textItem.width);
            rowHeight = textItem.height;
            textItem.destroy();
        }
    }
    menuWidth = Math.min(menuWidth, getDocRoot().width - menuPadding);
    return menuWidth;
}

function initializeMenu()
{
    // move the mouse area to the menu's parent element
    menuMouseArea.parent = menuRoot.parent;

    // move the contextual menu to the document's root
    menuRoot.parent = getDocRoot();
}

function getMenuHeight()
{
    return Math.min(rowHeight * model.count + 1, getDocRoot().height - menuPadding);
}

function showMenu(mouse)
{
    var mouseX = mouse.x;
    var mouseY = mouse.y;

    var absoluteX = mouseX;
    var absoluteY = mouseY;
    var element = menuMouseArea.parent;

    while(element != null)
    {
        absoluteX += element.x;
        absoluteY += element.y;
        element = element.parent;
    }

    menu.x = Math.max(0, Math.min(absoluteX - menu.width / 2, menuRoot.width - menu.width));
    menu.y = Math.max(0, Math.min(absoluteY - menu.height / 2, menuRoot.height - menu.height));
    menuRoot.state = "visible";
    menuList.forceActiveFocus();
}
function hideMenu()
{
    menuRoot.state = "";
}
