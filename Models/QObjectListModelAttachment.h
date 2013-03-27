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
#ifndef QObjectListAttachment_H
#define QObjectListAttachment_H

/*
can be used to provide list model accessors on objects that only provide non-changing qlists.

the resulting QObjectListModel is cached within a property in the attachedTo object.

e.g.:
Q_PROPERTY(QObjectListModel * shelves READ shelvesListAdapter CONSTANT );

QObjectListModel * Rack::shelvesListAdapter()
{
return attachedListModel<Shelf*>(this, "shelvesListAdapter", m_shelves);
}

QList<Shelf*> m_shelves;
*/

template<class T>
static QObjectListModel<T> * attachedListModel( QObject * attachedTo, const char * propertyName, const QList<T> &init_objects )
{
    QVariant list_variant = attachedTo->property(propertyName); // this property caches the list model
    if(list_variant.isValid())  // return cached
        if(QObject * list_object = qvariant_cast<QObject *>(list_variant))
            if(QbObjectListModel<T> * list_adapter = dynamic_cast<QbObjectListModel<T> *>(list_object))
            {
                if(list_adapter->objectList() != init_objects)
                    list_adapter->setObjectList(init_objects); //update if necessary
                return list_adapter;
            }
    // create new adapter
    QbObjectListModel<T> * list_adapter = new QbObjectListModel<T>(init_objects, attachedTo);
    attachedTo->setProperty(propertyName, QVariant(QMetaType::QObjectStar, &list_adapter));
    return list_adapter;
}

#endif
