#ifndef SYSTEM_H
#define SYSTEM_H
#include <memory>
#include <QObject>
#include <QStringList>
#include <QSurfaceFormat>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQuickView>
#include "_2RealApplication.h"
#include "_2RealDatatypes.h"


typedef std::shared_ptr<const _2Real::CustomType> CustomTypeRef;

namespace Uber {

    class FileLoader;
    class ConnectionManager;
    class ComplexDelegate;
    class Link;
    class Item;
    class ItemObjectListModel;
    class DockModel;

    class System : public QObject
    {
        Q_OBJECT
    public:
        inline static System*    getInstance()
        {
            if ( m_Instance == nullptr )
            {
                m_Instance = new System();
            }
            return m_Instance;
        }

        ~System();

        void                                createWindows();
        void                                loadQmlFiles();
        void                                loadBundles();
        void                                loadInterfaceBlocks();
        void                                setComplexDelegates();

        DockModel*                          getDockModel();
        ItemObjectListModel*                getItemModel();
        ConnectionManager*                  getConnectionManager();

        inline QQmlEngine*                  getQmlEngine()
        {
            return m_QmlEngine;
        }
        void                                registerQmlTypes();
        void                                setContextProperties();
        void                                enableTransparentWindows();
        void                                showWindows();
        Q_INVOKABLE void                    removeItem(Item* item);

        Q_INVOKABLE void                    addDockItem( int index );
        Q_INVOKABLE QPointF                 maptoGlobal(QQuickItem* item);
        Q_INVOKABLE QPointF                 getDockInputPosition();

        QQuickView*                         getWindow() const;

        FileLoader * fileLoader();
        FileLoader const* fileLoader() const;

        /*
         *  called by the so-called file loader when a file is supposed to be loaded
         */
        void loadConfig( QString const& dataSource );

    private:

        System();
        System(System const&);
        void operator=(System const&);

        static System               *m_Instance;

        _2Real::app::Engine         &m_2RealEngine;
        QQmlEngine                  *m_QmlEngine;

        DockModel                   *m_DockModel;
        ItemObjectListModel         *m_ItemModel;
        ComplexDelegate             *m_ComplexDelegate;

        QQuickView                  *m_CanvasWindow;
        QQuickView                  *m_DockWindow;
        FileLoader                  *m_FileLoader;
        ConnectionManager           *m_ConnectionManager;

    public slots:
//        void changedFocus(QObject * focusObject);
        void cleanup();
    };
    Q_DECLARE_METATYPE(std::shared_ptr<const _2Real::Image> )
}
#endif // UBSYSTEM_H
