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
#ifndef QObjectListModelIndex_H
#define QObjectListModelIndex_H

#include "QObjectListModelAdapter.h"
#include <QHash>

class QObjectListModelIndexByName : public QObjectListModelAdapter {
	Q_OBJECT;
public:
	QObjectListModelIndexByName(QObjectListModel * listModel, bool enabled = true, QObject * parent = NULL);

	bool containsObject(QObject * obj) const;
	bool containsName(const QString & name) const;
	int indexOfObject(QObject * obj) const;
	int indexOfName(const QString & name) const;

protected slots:
	void onNameChanged();
	void removeAllFromIndex();
	void onWatchRemovalsChanged();
protected:
	virtual void insertFor( int index, QObject * obj, int listCount );
	virtual void removeFor( int index, QObject * obj, int listCount );
	QHash<QString,int> m_hashmapName;
	QHash<QObject*,QString> m_hashmapObject;
	bool m_trackNameChanges;
};

#endif 