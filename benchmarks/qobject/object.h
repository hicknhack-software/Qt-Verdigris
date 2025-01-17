/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef OBJECT_H
#define OBJECT_H

#include <qobject.h>
#include "wobjectimpl.h"

class Object : public QObject
{
    Q_OBJECT
public:
    void emitSignal0();
    void emitSignal1();
signals:
    void signal0();
    void signal1();
    void signal2();
    void signal3();
    void signal4();
    void signal5();
    void signal6();
    void signal7();
    void signal8();
    void signal9();
public slots:
    void slot0();
    void slot1();
    void slot2();
    void slot3();
    void slot4();
    void slot5();
    void slot6();
    void slot7();
    void slot8();
    void slot9();
};

class ObjectW : public QObject
{
    W_OBJECT(ObjectW)
public:
    void emitSignal0();
    void emitSignal1();
//signals:
    void signal0() W_SIGNAL(signal0);
    void signal1() W_SIGNAL(signal1);
    void signal2() W_SIGNAL(signal2);
    void signal3() W_SIGNAL(signal3);
    void signal4() W_SIGNAL(signal4);
    void signal5() W_SIGNAL(signal5);
    void signal6() W_SIGNAL(signal6);
    void signal7() W_SIGNAL(signal7);
    void signal8() W_SIGNAL(signal8);
    void signal9() W_SIGNAL(signal9);

//public slots:
    void slot0(); W_SLOT(slot0);
    void slot1(); W_SLOT(slot1);
    void slot2(); W_SLOT(slot2);
    void slot3(); W_SLOT(slot3);
    void slot4(); W_SLOT(slot4);
    void slot5(); W_SLOT(slot5);
    void slot6(); W_SLOT(slot6);
    void slot7(); W_SLOT(slot7);
    void slot8(); W_SLOT(slot8);
    void slot9(); W_SLOT(slot9);
};

#endif // OBJECT_H
