#ifndef DOCKMODEL_H
#define DOCKMODEL_H

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QList>
#include <QSize>
#include <QUrl>
#include <QDebug>
#include <QCompleter>
#include "_2RealApplication.h"
#include "../items/Item.h"

namespace Uber {
    typedef QList<class GridEntry> GridEntryList;
    enum  GridEntryType { BlockType, SliderType, TextInputType, ImageType };
    class GridEntry
    {
    public:
        GridEntry(GridEntryType entryType = BlockType)
        :m_EntryType(entryType)
        {

        }

        void setName( const QString& name )
        {
            m_Name = name;
        }

        QString getName()const
        {
            return m_Name;
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
            m_EntryType = BlockType;
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

        bool    typeIs( GridEntryType type )
        {
            return ( type == m_EntryType );
        }

    private:
        QString                     m_Name;
        QUrl                        m_IconUrl;
        _2Real::app::BundleHandle   m_BundleHandle;
        GridEntryType               m_EntryType;
    };

    class DockModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(int count READ count NOTIFY countChanged)
    public:
        enum GridEntryRoles {
            PathRole = Qt::UserRole + 1,
            NameRole = PathRole + 1
        };
        explicit                DockModel(QObject *parent = 0);
        int                     rowCount(const QModelIndex & parent = QModelIndex()) const;
        QVariant                data(const QModelIndex & index, int role = Qt::DecorationRole) const;

        void                    addEntry( const GridEntry &entry );
        void                    addEntries( const GridEntryList& entries );

        Q_INVOKABLE QAbstractItemModel  * getCompletionModel(const QString& text);

        GridEntry               getEntry( int row );

        int                     count() const;
        QHash<int,QByteArray>   roleNames() const;

        Item*                   create( int row );
    signals:
        void                    countChanged();
    public slots:
    private:
        GridEntryList           m_Entries;
        QCompleter*             m_AutoCompleter;
    };
}
#endif // DOCKMODEL_H
