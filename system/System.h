#ifndef SYSTEM_H
#define SYSTEM_H
#include <QStringList>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickView>
#include "../models/DockModel.h"
#include "../models/ItemObjectListModel.h"
#include "_2RealApplication.h"
#include "_2RealDatatypes.h"
#include <QImage>

typedef std::shared_ptr<const _2Real::CustomType> CustomTypeRef;
namespace Uber {
    class FileLoader;
    class ConnectionManager;
    class ComplexDelegate;
    class Link;

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

        Q_INVOKABLE void                    addDockItem( int index );
        Q_INVOKABLE QPointF                 maptoGlobal(QQuickItem* item);
        Q_INVOKABLE QPointF                 getDockInputPosition();

        QQuickView*                         getWindow() const;

        //static QObject *blargh( QQmlEngine *engine, QJSEngine *scriptEngine )
        //{
        //    Q_UNUSED(engine)
        //    Q_UNUSED(scriptEngine)
        //    return getInstance();
        //}

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

        static System*                      m_Instance;
        QStringList                         m_BundleFilenames;
        DockModel*                          m_DockModel;
        ItemObjectListModel*                m_ItemModel;
        _2Real::app::Engine&                m_Engine;
        QQmlEngine*                         m_QmlEngine;
        ComplexDelegate*                    m_ComplexDelegate;
        QQuickView*                         m_Canvas;
        QQuickView*                         m_Dock;
        QSurfaceFormat                      m_SurfaceFormat;

        FileLoader                          *mFileLoader;
        Link*                               m_CurrentLink;
        ConnectionManager                   *m_ConnectionManager;
    public slots:
        void changedFocus(QObject * focusObject);
        void cleanup()
        {
            qDebug() << "Cleanup called";
//            if ( m_Dock )
//                delete m_Dock;
//            if ( m_Canvas )
//                delete m_Canvas;
        }
    };
    Q_DECLARE_METATYPE(std::shared_ptr<const _2Real::CustomType> )
}
#endif // UBSYSTEM_H
