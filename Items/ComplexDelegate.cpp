#include "ComplexDelegate.h"
#include "../System.h"

namespace Uber {
    ComplexDelegate::ComplexDelegate(QObject *parent)
    :QObject(parent)
    {
        std::cout << "WTF!!!" << std::endl;
    }

    void ComplexDelegate::addDelegate(QString modelType, QUrl fileUrl)
    {
        if ( m_DelegateStore.contains(modelType) )
            return;
        m_DelegateStore.insert( modelType, fileUrl );
    }

    void ComplexDelegate::setDelegate(QString modelType, QUrl fileUrl)
    {
        if ( !m_DelegateStore.contains(modelType) )
            return;
        m_DelegateStore[modelType] = fileUrl;
        emit delegateChanged(modelType);
    }

    QUrl ComplexDelegate::getDelegate(QString modelType)
    {
        if ( !m_DelegateStore.contains(modelType) )
            return QUrl();
        std::cout << "WTF!!!" << std::endl;
        std::cout << modelType.toUtf8().constData() << std::endl;
        return m_DelegateStore.value(modelType);
    }
}
