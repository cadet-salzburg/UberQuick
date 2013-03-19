#ifndef SYSTEM_H
#define SYSTEM_H
#include <QStringList>
#include <QQmlEngine>
#include <QQuickItem>
#include "Models/DockModel.h"
#include "_2RealApplication.h"
namespace Uber {
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
        void                            loadBundles();
        DockModel*                      getDockModel();
        inline QQmlEngine*              getQmlEngine()
        {
            return m_QmlEngine;
        }
        Q_INVOKABLE QPointF  maptoGlobal(QQuickItem* item);

    private:
        System();
        System(System const&);// Don't Implement
        void operator=(System const&); // Don't implement
        static System*                  m_Instance;
        QStringList                     m_BundleFilenames;
        DockModel*                      m_DockModel;
        _2Real::app::Engine&            m_Engine;
        QQmlEngine*                     m_QmlEngine;
    };
}
#endif // UBSYSTEM_H
