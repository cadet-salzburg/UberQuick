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
#include "QObjectListModelIndex.h"
#include "QObjectListModel.h"


QObjectListModelIndexByName::QObjectListModelIndexByName( QObjectListModel * listModel, bool enabled /*= true*/, QObject * parent /*= NULL*/ )
	: QObjectListModelAdapter(listModel, enabled, parent)
	, m_trackNameChanges(true)
{
	connect(this,SIGNAL(watchRemovalsChanged()),this,SLOT(onWatchRemovalsChanged()));
	onWatchRemovalsChanged();
}

int QObjectListModelIndexByName::indexOfName( const QString & name ) const
{
	int idx = m_hashmapName.value(name, -1);
	return idx;
}

int QObjectListModelIndexByName::indexOfObject( QObject * obj ) const
{
	if(!m_hashmapObject.contains(obj)) 
		return -1;
	int idx = indexOfName(m_hashmapObject.value(obj));
	Q_ASSERT(!containsObject(obj) || listModel()->at(idx) == obj);
	return idx;
}

void QObjectListModelIndexByName::insertFor( int index, QObject * obj, int listCount )
{
	const QString & name = obj->objectName();
	if(m_hashmapName.contains(name))
	{
		qWarning()<<"name index has duplicate entry: "<<name;
		return;
	}
	m_hashmapName.insert(name, index);
	m_hashmapObject.insert(obj, name); // always save original object name, it can change
	if(m_trackNameChanges)
	{
		// try to connect to nameChanged signal if existing (like for qbobjects)
		connect(obj, SIGNAL(nameChanged()), this, SLOT(onNameChanged()));
	}

	// update indices > index
	for(int i=index+1; i < listCount; ++i)
		m_hashmapName.insert(listModel()->at(i)->objectName(), i);
}

void QObjectListModelIndexByName::removeFor( int index, QObject * obj, int listCount )
{
	if(!m_hashmapObject.contains(obj)) 
		return;
	// remove by original name (name could have changed after indexing)
	m_hashmapName.remove(m_hashmapObject.value(obj));
	m_hashmapObject.remove(obj);

	// update indices > index
	int n = listModel()->count();
	for(int i=index+1; i < listCount; ++i)
		m_hashmapName.insert(listModel()->at(i)->objectName(), i-1);
}

void QObjectListModelIndexByName::removeAllFromIndex()
{
	m_hashmapName.clear();
	m_hashmapObject.clear();
}

void QObjectListModelIndexByName::onWatchRemovalsChanged()
{
	if(watchRemovals())
	{
		disconnect(listModel(), SIGNAL(modelAboutToBeReset()), this, SLOT(removeAll())); // override remove all -> efficiency
		connect(listModel(), SIGNAL(modelAboutToBeReset()), this, SLOT(removeAllFromIndex()));
	}
	else
	{
		disconnect(listModel(), SIGNAL(modelAboutToBeReset()), this, SLOT(removeAllFromIndex()));
	}
}

void QObjectListModelIndexByName::onNameChanged()
{
	QObject * obj = sender();
	int index = indexOfObject(obj);
	removeFor(index, obj, index+1);
	m_trackNameChanges = false;
	insertFor(index, obj, index+1);
	m_trackNameChanges = true; // must have been true before, this function has been called because of this
}

bool QObjectListModelIndexByName::containsObject( QObject * obj ) const
{
	return m_hashmapObject.contains(obj);
}

bool QObjectListModelIndexByName::containsName( const QString & name ) const
{
	return m_hashmapName.contains(name);
}
