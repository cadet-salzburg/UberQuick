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

#QML_IMPORT_PATH =

SOURCES += \
    main.cpp \
    Image.cpp \
    System.cpp \
    Models/DockModel.cpp \
    Models/BlockModel.cpp \
    Items/Outlet.cpp \
    Items/Item.cpp \
    Items/Inlet.cpp \
    Items/Connection.cpp \
    Items/Block.cpp \
    Items/Workbench.cpp \
    Items/ComplexDelegate.cpp \
    Models/GraphModel.cpp \
    Models/QObjectListModel.cpp \
    Models/BlockObjectListModel.cpp \
    Models/LinkObjectListModel.cpp

HEADERS += \
    System.h \
    Models/DockModel.h \
    Models/BlockModel.h \
    Items/Outlet.h \
    Items/Item.h \
    Items/Inlet.h \
    Items/Connection.h \
    Items/Block.h \
    Items/Workbench.h \
    Items/ComplexDelegate.h \
    Models/GraphModel.h \
    Image.h \
    Models/QObjectListModelT.h \
    Models/QObjectListModelAttachment.h \
    Models/QObjectListModel.h \
    Models/ItemObjectListModel.h \
    Models/BlockObjectListModel.h \
    Models/LinkObjectListModel.h

OTHER_FILES += \
    qml/Dock/Dock.qml \
    qml/Workbench/TaskBar.qml \
    qml/Workbench/MainWindow.qml \
    qml/UI/Button.qml \
    qml/Workbench/Block.qml \
    qml/Workbench/Inlet.qml


#Includes
INCLUDEPATH += $(_2REAL_DEPENDENCIES_DIR)/eigen
INCLUDEPATH += $(_2REAL_DEPENDENCIES_DIR)/poco/bin
INCLUDEPATH += $(_2REAL_DEPENDENCIES_DIR)/poco/Foundation/include
INCLUDEPATH += $(_2REAL_DIR)/kernel/src

#Linking
win32:CONFIG(release, debug|release): LIBS += -L$(_2REAL_DIR)/kernel/lib/ -l_2RealFramework_32
else:win32:CONFIG(debug, debug|release): LIBS += -L$(_2REAL_DIR)/kernel/lib/ -l_2RealFramework_32d
win32:CONFIG(release, debug|release): LIBS += -L$(_2REAL_DEPENDENCIES_DIR)/poco/lib/ -lPocoFoundation
else:win32:CONFIG(debug, debug|release): LIBS += -L$(_2REAL_DEPENDENCIES_DIR)/poco/lib/ -lPocoFoundationd
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
