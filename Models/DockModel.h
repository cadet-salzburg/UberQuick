#ifndef DOCKMODEL_H
#define DOCKMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QSize>
#include <QUrl>
#include <QDebug>
#include "_2RealApplication.h"
namespace Uber {
    typedef QList<class GridEntry> GridEntryList;
    class GridEntry
    {
    public:
        GridEntry()
//        :m_BlockName(QString())
//        ,m_IconUrl(QUrl())
//        ,m_BundleHandle()
        {

        }

        void setBlockName( const QString& name )
        {
            m_BlockName = name;
        }

        QString getBlockName()const
        {
            return m_BlockName;
        }

        void setIconUrl( const QUrl& iconUrl )
        {
            m_IconUrl = iconUrl;
        }

        QUrl getIconUrl() const
        {
            return m_IconUrl;
        }

        void setBundleHandle( _2Real::app::BundleHandle handle )
        {
            m_BundleHandle = handle;
        }

        _2Real::app::BundleHandle getBundleHandle()
        {
            return m_BundleHandle;
        }

        QSize getSize() const
        {
            return QSize();
            //return m_Image.count();
        }

    private:
        QString                     m_BlockName;
        QUrl                        m_IconUrl;
        _2Real::app::BundleHandle   m_BundleHandle;
    };



    class DockModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(int count READ count NOTIFY countChanged)
    public:
        enum GridEntryRoles {
            PathRole = Qt::UserRole + 1,
            NameRole
        };
        explicit                DockModel(QObject *parent = 0);
        int                     rowCount(const QModelIndex & parent = QModelIndex()) const;
        QVariant                data(const QModelIndex & index, int role = Qt::DecorationRole) const;

        void                    addEntry( const GridEntry &entry );
        void                    addEntries( const GridEntryList& entries );

        int                     count() const;
        QHash<int,QByteArray>   roleNames() const;
    signals:
        void                    countChanged();
    public slots:
    private:
        GridEntryList           m_Entries;
    };
}
#endif // DOCKMODEL_H
