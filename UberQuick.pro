# Add more folders to ship with the application, here
folder_01.source += qml/*
folder_01.target = qml
folder_02.source += images/*
folder_02.target = images
folder_03.source += blocks/*
folder_03.target = blocks

DEPLOYMENTFOLDERS = folder_01
DEPLOYMENTFOLDERS += folder_02
DEPLOYMENTFOLDERS += folder_03

SOURCES += \
    main.cpp \
    models/QObjectListModel.cpp \
    models/OutletObjectListModel.cpp \
    models/ItemObjectListModel.cpp \
    models/InletObjectListModel.cpp \
    models/DockModel.cpp \
    items/Workbench.cpp \
    items/Slider.cpp \
    items/Link.cpp \
    items/Item.cpp \
    items/Inlet.cpp \
    items/Circle.cpp \
    items/Canvas.cpp \
    items/Block.cpp \
    items/BezierCurve.cpp \
    system/ComplexDelegate.cpp \
    system/System.cpp \
    system/FileLoader.cpp \
    system/EventFilter.cpp \
    system/ConnectionManager.cpp \
    items/Outlet.cpp \
    items/BlockInlet.cpp \
    items/BlockOutlet.cpp \
    items/InterfaceInlet.cpp \
    items/InterfaceElement.cpp \
    items/InterfaceOutlet.cpp

HEADERS += \
    models/QObjectListModelT.h \
    models/QObjectListModelAttachment.h \
    models/QObjectListModel.h \
    models/OutletObjectListModel.h \
    models/ItemObjectListModel.h \
    models/InletObjectListModel.h \
    models/DockModel.h \
    items/Workbench.h \
    items/Outlet.h \
    items/Link.h \
    items/Item.h \
    items/Inlet.h \
    items/Circle.h \
    items/Canvas.h \
    items/Block.h \
    items/BezierCurve.h \
    system/ComplexDelegate.h \
    system/System.h \
    system/FileLoader.h \
    system/EventFilter.h \
    items/Slider.h \
    system/ConnectionManager.h \
    items/BlockInlet.h \
    items/BlockOutlet.h \
    items/InterfaceInlet.h \
    items/InterfaceElement.h \
    items/InterfaceOutlet.h

OTHER_FILES += \
    qml/Dock/Dock.qml \
    qml/Workbench/TaskBar.qml \
    qml/Workbench/MainWindow.qml \
    qml/UI/Button.qml \
    qml/UI/Tooltip.qml \
    qml/UI/FileDialog.qml \
    qml/Workbench/Link.qml \
    qml/Workbench/Node.qml \
    qml/Workbench/Inlets.qml \
    qml/Workbench/Outlets.qml \
    qml/Block/Node.qml \
    qml/Block/Link.qml \
    qml/Block/Block.qml \
    qml/Block/NodeRow.qml \
    qml/Block/CanvasConnection.qml \
    qml/UI/Slider.qml \
    qml/UI/BaseBlock.qml \
    qml/UI/SliderNew.qml


#Includes
INCLUDEPATH += $(_2REAL_DEPENDENCIES_DIR)/eigen
INCLUDEPATH += $(_2REAL_DEPENDENCIES_DIR)/poco/bin
INCLUDEPATH += $(_2REAL_DEPENDENCIES_DIR)/poco/Foundation/include
INCLUDEPATH += $(_2REAL_DIR)/kernel/src
INCLUDEPATH += $$PWD/../../../Qt/Qt5.0.1/5.0.1/msvc2010/include
INCLUDEPATH += C:/Qt/Qt5.0.1/5.0.1/msvc2010/include/QtQuick/5.0.1/QtQuick
INCLUDEPATH += C:/Qt/Qt5.0.1/5.0.1/msvc2010/include/QtQuick/5.0.1/QtQuick/privatez
INCLUDEPATH += C:/Qt/Qt5.0.1/5.0.1/msvc2010/include/QtCore/5.0.1
INCLUDEPATH += items/
INCLUDEPATH += models/
INCLUDEPATH += system/


#Linking
win32:CONFIG(release, debug|release): LIBS += -L$(_2REAL_DIR)/kernel/lib/ -l_2RealFramework_32
else:win32:CONFIG(debug, debug|release): LIBS += -L$(_2REAL_DIR)/kernel/lib/ -l_2RealFramework_32d
win32:CONFIG(release, debug|release): LIBS += -L$(_2REAL_DEPENDENCIES_DIR)/poco/lib/ -lPocoFoundation
else:win32:CONFIG(debug, debug|release): LIBS += -L$(_2REAL_DEPENDENCIES_DIR)/poco/lib/ -lPocoFoundationd
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Qt/Qt5.0.1/5.0.1/msvc2010/lib/ -lQt5Widgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Qt/Qt5.0.1/5.0.1/msvc2010/lib/ -lQt5Widgetsd

LIBS += -ldwmapi

#Copy needed dlls to dest dir
win32 {
    #...
    EXTRA_BINFILES += \
	$(_2REAL_DEPENDENCIES_DIR)/poco/bin/PocoFoundation.dll \
	$(_2REAL_DEPENDENCIES_DIR)/poco/bin/PocoFoundationd.dll \
	$(_2REAL_DEPENDENCIES_DIR)/poco/bin/PocoXML.dll \
	$(_2REAL_DEPENDENCIES_DIR)/poco/bin/PocoXMLd.dll \
	$(_2REAL_DEPENDENCIES_DIR)/videoinputlib/lib/videoInput_mtd_32.dll \
	$(_2REAL_DEPENDENCIES_DIR)/videoinputlib/lib/videoInput_mtd_32d.dll \
	$(_2REAL_DEPENDENCIES_DIR)/opencv/lib/vc10/bin/opencv_core242.dll \
	$(_2REAL_DEPENDENCIES_DIR)/opencv/lib/vc10/bin/opencv_core242d.dll \
	$(_2REAL_DEPENDENCIES_DIR)/opencv/lib/vc10/bin/opencv_imgproc242.dll \
	$(_2REAL_DEPENDENCIES_DIR)/opencv/lib/vc10/bin/opencv_imgproc242d.dll \
	$(_2REAL_DEPENDENCIES_DIR)/tbb/bin/tbb.dll \
	$(_2REAL_DEPENDENCIES_DIR)/tbb/bin/tbb_debug.dll

    EXTRA_BINFILES_WIN = $${EXTRA_BINFILES}
    EXTRA_BINFILES_WIN ~= s,/,\\,g
	DESTDIR_WIN = $${DESTDIR}
    DESTDIR_WIN ~= s,/,\\,g
    for(FILE,EXTRA_BINFILES_WIN){
		QMAKE_POST_LINK +=$$quote(cmd /c copy /y $${FILE} $${DESTDIR_WIN}$$escape_expand(\n\t))
    }
}
# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()
