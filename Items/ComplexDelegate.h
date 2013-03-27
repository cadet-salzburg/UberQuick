#ifndef COMPLEXDELEGATE_H
#define COMPLEXDELEGATE_H
#include <QObject>
#include <QQmlComponent>
#include <QUrl>
#include <QMap>

namespace Uber {
    class ComplexDelegate : public QObject
    {
        Q_OBJECT
    public:
        ComplexDelegate(QObject *parent = 0);
        Q_INVOKABLE void                addDelegate( QString modelType, QUrl fileUrl );
        Q_INVOKABLE void                setDelegate( QString modelType, QUrl fileUrl );
        Q_INVOKABLE QUrl                getDelegate( QString modelType );
    signals:
        void                            delegateChanged(QString);
    public slots:
    private:
        QMap<QString, QUrl>             m_DelegateStore;
    };
}
#endif // COMPLEXDELEGATE_H
