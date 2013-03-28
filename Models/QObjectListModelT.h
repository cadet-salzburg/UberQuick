/****************************************************************************
**
** Copyright (C) 2012 IPO.Plan GmbH
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
#ifndef QObjectListModelT_H
#define QObjectListModelT_H
#include "QObjectListModel.h"
/*
subclass QObjectListModelT<T> to work with a typed QObjectListModel,
e.g.
class RackObjectListModel : public QObjectListModelT<Rack*> {
};
*/

template <class T>
class QObjectListModelT : public QObjectListModel {
public:
    QObjectListModelT<T>(QObject *parent = 0) : QObjectListModel(parent) { }
    QObjectListModelT(const QList<T> &objects, QObject *parent = 0);
    QObjectListModelT(QObjectListModelT<T> *objectListModel, QObject *parent = 0) : QObjectListModel(objectListModel, parent) { }
    QList<T> objectList() const;
    void setObjectList(const QList<T> &objects);
    inline T at(int i) const { return (T)(m_objects.at(i)); }
    inline T operator[](int i) const { return (T)m_objects[i]; }
    inline T first() const { return (T)m_objects.at(0); }
    inline T last() const { return (T)m_objects.last(); }

    T get(const int i) const;
    T getByName(const QString &str) const;
};

template <class T>
T QObjectListModelT<T>::getByName( const QString &str ) const
{
    return (T)QObjectListModel::getByName(str);
}

template <class T>
T QObjectListModelT<T>::get( const int i ) const
{
    return (T)QObjectListModel::get(i);
}

template <class T>
QObjectListModelT<T>::QObjectListModelT( const QList<T> &objects, QObject *parent /*= 0*/ ) : QObjectListModel(parent)
{
    setObjectList(objects);
}

template <class T>
void QObjectListModelT<T>::setObjectList( const QList<T> &objects )
{
    QObjectListModel::setObjectList(*reinterpret_cast<const QList<QObject*>*>(&objects));
}

template <class T>
QList<T> QObjectListModelT<T>::objectList() const
{
    return *reinterpret_cast<QList<T>*>(&QObjectListModel::objectList());
}

#define DECLARE_QBLIST_MODEL(CLASSNAME, TYPENAME) class CLASSNAME : public QObjectListModelT<TYPENAME>  { \
    Q_OBJECT \
public: \
    CLASSNAME(QObject *parent=NULL):QObjectListModelT<TYPENAME>(parent) {} \
};

#endif
