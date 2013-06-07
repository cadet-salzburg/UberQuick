#ifndef SYSTEM_H
#define SYSTEM_H
#include <QStringList>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickView>

#include "Models/DockModel.h"
#include "Models/ItemObjectListModel.h"
#include "_2RealApplication.h"


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
        void                                loadBundles();
        void                                loadQmlFiles();
        DockModel*                          getDockModel();
        ItemObjectListModel*                getItemModel();
        inline QQmlEngine*                  getQmlEngine()
        {
            return m_QmlEngine;
        }
        void                                registerQmlTypes();
        void                                setContextProperties();
        void                                enableTransparentWindows();
        void                                showWindows();

        Q_INVOKABLE void                    addBlock( int index );
        Q_INVOKABLE QPointF                 maptoGlobal(QQuickItem* item);
        Q_INVOKABLE QPointF                 getDockInputPosition();


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

    };
}
#endif // UBSYSTEM_H
