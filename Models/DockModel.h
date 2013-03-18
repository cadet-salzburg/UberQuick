#ifndef DOCKMODEL_H
#define DOCKMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QSize>
#include <QUrl>
#include <QDebug>

namespace Uber {
    class GridEntry
    {
    public:
        GridEntry()
        {
        }

        GridEntry(const QString& name, const QUrl& image = QUrl("../../images/arduino.svg") )
        :m_Name(name)
        ,m_Image(image)
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

        void setImage( const QUrl& img )
        {
            m_Image = img;
            qDebug() << "image set";
        }

        QUrl getImage() const
        {
            return m_Image;
        }

        QSize getSize() const
        {
            return QSize();
            //return m_Image.count();
        }

    private:
        QString         m_Name;
        QUrl            m_Image;
    };

    typedef QList<GridEntry> GridEntryList;

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
        QList<GridEntry>      m_Entries;
    };
}
#endif // DOCKMODEL_H
