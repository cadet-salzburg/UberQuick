/****************************************************************************
**
** Copyright (C) 2012 IPO.Plan GmbH
**
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QOBJECTLISTMODEL_H
#define QOBJECTLISTMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>

/*
QObjectListModel presents a way to store QObject pointers in a list
which actively sends signals on list change.
It is thus suited for use as QML data storage whith change notification.
When using subclasses of QObjectListModelT, one can even achieve
static type checking on the C++ side.
*/

class QObjectListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    explicit QObjectListModel(QObject *parent = 0);
    QObjectListModel(const QList<QObject*> &objects, QObject *parent = 0);
    QObjectListModel(QObjectListModel *objectListModel, QObject *parent = 0);
    virtual ~QObjectListModel();

    inline QObject * parent() const { return QObject::parent(); }

    // connects destroy signals
    void setTracking(bool v ) { m_tracking = v; }
    void trackObject(const QObject *obj, const bool on );

    //model API
    enum Roles {
        ObjectRole =    Qt::UserRole+1
    };

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QVariant dataByRole(const int i, int role) const;

    // directly access underlying QList data storage
    QList<QObject*> objectList() const;
    void setObjectList(const QList<QObject*> &objects);

    //list API
    void append(QObject *object);
    void append(const QList<QObject*> &objects);
    void insert(int i, QObject *object);
    void insert(int i, const QList<QObject*> &objects);
    inline QObject *first() const { return m_objects.at(0); }
    inline QObject *last() const { return m_objects.last(); }
    inline QObject *at(int i) const { return m_objects.at(i); }
    inline QObject *operator[](int i) const { return m_objects[i]; }

    void replace(int i, QObject *object);
    void move(int from, int to);

    void removeAt(int i, int count = 1);
    QObject *takeAt(int i);
    void clear(bool deleteObjects=false);

    bool contains(QObject *object) const;
    bool containsName(const QString & str) const;
    Q_INVOKABLE int indexOf (QObject *object, int from = 0) const;
    inline int lastIndexOf (QObject *object, int from = -1) const { return m_objects.lastIndexOf(object, from); }
    Q_INVOKABLE int indexOfName (const QString & str) const;

    inline int count() const { return m_objects.count(); }
    //inline int size() const { return m_objects.size(); }
    inline bool isEmpty() const { return m_objects.isEmpty(); }

    //additional QML API
    Q_INVOKABLE QObject *get(const int i) const;
    Q_INVOKABLE QObject *getByName( const QString & str) const;
    Q_INVOKABLE void listAppend(QObject * obj);
    Q_INVOKABLE void listInsert(int at, QObject * obj);
    Q_INVOKABLE void listRemove(int at, int count=1);
    Q_INVOKABLE void listSetFromObjectListModel(QObjectListModel* model);
    Q_INVOKABLE void listSetFromItemModel(QAbstractItemModel* model, int role=ObjectRole, int column=0);

    void sortByName();

    void dump() const; // print object names
    void touch(); // issues modelreset

    QHash<int, QByteArray> roleNames() const
    {
        QHash<int, QByteArray> roles;
        roles[QObjectListModel::ObjectRole] = "object";
        return roles;
    }

    // set up index for objects and their names
    // speeds up contains/indexOf/indexOfName etc...
    //inline bool hasIndexByName() const { return m_indexByName!=nullptr; }
    //void setIndexByName(bool enable);

signals:
    void countChanged();

protected slots:
    void onObjectDestroyed( QObject *obj );

protected:
    QList<QObject*> m_objects;
    bool m_tracking;
    //QObjectListModelIndexByName * m_indexByName;

#ifdef _DEBUG
    // to record access patterns to decide if indexing is useful
    int m_accessCountIndexOfObject;
    int m_accessCountIndexOfName;
#endif
};
#endif // QOBJECTMODEL_H
