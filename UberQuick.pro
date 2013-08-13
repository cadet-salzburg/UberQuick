# Add more folders to ship with the application, here
folder_01.source += qml/*
folder_01.target = qml
#folder_02.source += images/*
#folder_02.target = images
folder_03.source += blocks/*
folder_03.target = blocks
folder_04.source += js/*
folder_04.target = js

DEPLOYMENTFOLDERS = folder_01
#DEPLOYMENTFOLDERS += folder_02
DEPLOYMENTFOLDERS += folder_03
DEPLOYMENTFOLDERS += folder_04

SOURCES += \
    main.cpp \
    models/QObjectListModel.cpp \
    models/OutletObjectListModel.cpp \
    models/ItemObjectListModel.cpp \
    models/InletObjectListModel.cpp \
    models/DockModel.cpp \
    models/StringModel.cpp \
    system/ComplexDelegate.cpp \
    system/System.cpp \
    system/FileLoader.cpp \
    system/ConnectionManager.cpp \
    items/Link.cpp \
    items/Item.cpp \
    items/BaseInlet.cpp \
    items/BaseOutlet.cpp \
    items/FrameworkInlet.cpp \
    items/FrameworkOutlet.cpp \
    items/InterfaceInlet.cpp \
    items/InterfaceOutlet.cpp \
    items/StringObject.cpp \
    qml_extensions/UberTexture.cpp \
    qml_extensions/PixelView.cpp \
    qml_extensions/PainterBezier.cpp \
    qml_extensions/Circle.cpp \
    qml_extensions/Canvas.cpp \
    qml_extensions/BezierCurve.cpp \
    ui_items/TextIO.cpp \
    ui_items/SliderBlock.cpp \
    ui_items/InterfaceBlock.cpp \
    ui_items/Image.cpp \
    items/BaseBlock.cpp \
    items/FrameworkBlock.cpp
HEADERS += \
models/QObjectListModelT.h \
    models/QObjectListModelAttachment.h \
    models/QObjectListModel.h \
    models/OutletObjectListModel.h \
    models/ItemObjectListModel.h \
    models/InletObjectListModel.h \
    models/DockModel.h \
    models/StringModel.h \
    system/ComplexDelegate.h \
    system/System.h \
    system/FileLoader.h \
    system/ConnectionManager.h \
    system/Converter.h \
    system/Converter_T.h \
    system/ConverterFromDescription.h \
    items/BaseOutlet.h \
    items/Link.h \
    items/Item.h \
    items/BaseInlet.h \
    items/FrameworkInlet.h \
    items/FrameworkOutlet.h \
    items/InterfaceInlet.h \
    items/InterfaceOutlet.h \
    qml_extensions/UberTexture.h \
    qml_extensions/PixelView.h \
    qml_extensions/PainterBezier.h \
    qml_extensions/Circle.h \
    qml_extensions/Canvas.h \
    qml_extensions/BezierCurve.h \
    ui_items/TextIO.h \
    ui_items/SliderBlock.h \
    ui_items/InterfaceBlock.h \
    ui_items/Image.h \
    items/StringObject.h \
    items/BaseBlock.h \
    items/FrameworkBlock.h

OTHER_FILES += \
    qml/Canvas/Tooltip.qml \
    qml/Canvas/Node.qml \
    qml/Canvas/NodeRow.qml \
    qml/Canvas/ObjectFrame.qml \
    qml/Canvas/BaseBlock.qml \
    qml/Canvas/UberBlock.qml \
    qml/Canvas/SliderBlock.qml \
    qml/Canvas/ImageBlock.qml \
    qml/Canvas/Link.qml \
    qml/Canvas/Button.qml \
    qml/Canvas/TextBlock.qml \
    qml/Canvas/TextElement.qml \
    qml/Windows/TaskBar.qml \
    qml/Windows/MainWindow.qml \
    qml/Windows/Dock.qml \
    qml/Windows/ContextMenu.qml \
    qml/Windows/DockTextBrowser.qml \
    images/textedit.sci \
    js/ContextMenu.js \
    js/Bezier.js

#Includes
INCLUDEPATH += $(_2REAL_DEPENDENCIES_DIR)/eigen
INCLUDEPATH += $(_2REAL_DEPENDENCIES_DIR)/poco/bin
INCLUDEPATH += $(_2REAL_DEPENDENCIES_DIR)/poco/Foundation/include
INCLUDEPATH += $(_2REAL_DEPENDENCIES_DIR)/vld/include
INCLUDEPATH += $(_2REAL_DIR)/kernel/src
INCLUDEPATH += items/
INCLUDEPATH += models/
INCLUDEPATH += system/
INCLUDEPATH += qml_extensions/
INCLUDEPATH += ui_items/

#Linking
CONFIG += qt
QT += opengl

win32:CONFIG(release, debug|release): LIBS += -L$(_2REAL_DIR)/kernel/lib/ -l_2RealFramework_32
else:win32:CONFIG(debug, debug|release): LIBS += -L$(_2REAL_DIR)/kernel/lib/ -l_2RealFramework_32d
win32:CONFIG(release, debug|release): LIBS += -L$(_2REAL_DEPENDENCIES_DIR)/poco/lib/ -lPocoFoundation
else:win32:CONFIG(debug, debug|release): LIBS += -L$(_2REAL_DEPENDENCIES_DIR)/poco/lib/ -lPocoFoundationd
win32:CONFIG(debug, debug|release): LIBS += -L$(_2REAL_DEPENDENCIES_DIR)/vld/lib/Win32/ -lvld

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

RESOURCES += \
    uberquick.qrc
