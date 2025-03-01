/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Copyright (C) 2015 Olivier Goffart <ogoffart@woboq.com>
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


#include <QtTest/QtTest>

#include <qobject.h>
#include <qmetaobject.h>
#include <wobjectimpl.h>

struct CustomType
{
    int padding;
    QString str;
    CustomType(const QString &str = QString()) : str(str) {}
    operator QString() const { return str; }
    friend bool operator!=(const CustomType &a, const CustomType &b)
    { return a.str != b.str; }
};

Q_DECLARE_METATYPE(CustomType)

class tst_QMetaProperty : public QObject
{
    W_OBJECT(tst_QMetaProperty)

private slots:
#define DECLARE_TEST(NAME) void NAME(); W_SLOT(NAME)
    DECLARE_TEST(hasStdCppSet);
    DECLARE_TEST(isConstant);
    DECLARE_TEST(isFinal);
    DECLARE_TEST(gadget);
    DECLARE_TEST(readAndWriteWithLazyRegistration);
    DECLARE_TEST(mapProperty);
    DECLARE_TEST(conversion);
    DECLARE_TEST(enumsFlags);
#undef DECLARE_TEST

public:
    enum EnumType { EnumType1 };

    void setValue(EnumType) {}
    EnumType getValue() const { return EnumType1; }
    void set_value(EnumType) {}
    EnumType get_value() const { return EnumType1; }

    void resetValue7() { value7 = QStringLiteral("reset"); }
    int value8() const { return 1; }
    int value9() const { return 1; }
    int value10() const { return 1; }

    QString value7;
    QMap<int, int> map;
    CustomType custom;

    W_PROPERTY(EnumType, value WRITE setValue READ getValue);
    W_PROPERTY(EnumType, value2 WRITE set_value READ get_value);
    W_PROPERTY(QString, value7 MEMBER value7 RESET resetValue7);
    W_PROPERTY(int, value8 READ value8);
    W_PROPERTY(int, value9 READ value9 CONSTANT);
    W_PROPERTY(int, value10 READ value10 FINAL);
    W_PROPERTY((QMap<int, int>), map MEMBER map);
    W_PROPERTY(CustomType, custom MEMBER custom);

};

W_OBJECT_IMPL(tst_QMetaProperty)

void tst_QMetaProperty::hasStdCppSet()
{
    QSKIP("Not supported by W_PROPERTY");
    const QMetaObject *mo = metaObject();

    QMetaProperty prop = mo->property(mo->indexOfProperty("value"));
    QVERIFY(prop.isValid());
    QVERIFY(prop.hasStdCppSet());

    prop = mo->property(mo->indexOfProperty("value2"));
    QVERIFY(prop.isValid());
    QVERIFY(!prop.hasStdCppSet());
}

void tst_QMetaProperty::isConstant()
{
    const QMetaObject *mo = metaObject();

    QMetaProperty prop = mo->property(mo->indexOfProperty("value8"));
    QVERIFY(prop.isValid());
    QVERIFY(!prop.isConstant());

    prop = mo->property(mo->indexOfProperty("value9"));
    QVERIFY(prop.isValid());
    QVERIFY(prop.isConstant());
}

void tst_QMetaProperty::isFinal()
{
    const QMetaObject *mo = metaObject();

    QMetaProperty prop = mo->property(mo->indexOfProperty("value10"));
    QVERIFY(prop.isValid());
    QVERIFY(prop.isFinal());

    prop = mo->property(mo->indexOfProperty("value9"));
    QVERIFY(prop.isValid());
    QVERIFY(!prop.isFinal());
}

class MyGadget {
public:
    QString m_value;
    void setValue(const QString &value) { m_value = value; }
    QString getValue() { return m_value; }
    void resetValue() { m_value = QLatin1String("reset"); }
    W_GADGET(MyGadget)
    W_PROPERTY(QString, value READ getValue WRITE setValue RESET resetValue);
};

W_GADGET_IMPL(MyGadget)

void tst_QMetaProperty::gadget()
{
    const QMetaObject *mo = &MyGadget::staticMetaObject;
    QMetaProperty valueProp = mo->property(mo->indexOfProperty("value"));
    QVERIFY(valueProp.isValid());
    QCOMPARE(valueProp.metaType(), QMetaType::fromType<QString>());
    {
        MyGadget g;
        QString hello = QLatin1String("hello");
        QVERIFY(valueProp.writeOnGadget(&g, hello));
        QCOMPARE(g.m_value, QLatin1String("hello"));
        QCOMPARE(valueProp.readOnGadget(&g), QVariant(hello));
        QVERIFY(valueProp.resetOnGadget(&g));
        QCOMPARE(valueProp.readOnGadget(&g), QVariant(QLatin1String("reset")));
    }
}

struct CustomReadObject : QObject
{
    W_OBJECT(CustomReadObject)
};

struct CustomWriteObject : QObject
{
    W_OBJECT(CustomWriteObject)
};

struct CustomWriteObjectChild : CustomWriteObject
{
    W_OBJECT(CustomWriteObjectChild)
};

struct TypeLazyRegistration : QObject
{
    W_OBJECT(TypeLazyRegistration)
    CustomReadObject *_read;
    CustomWriteObject *_write;
    W_PROPERTY(CustomReadObject *,read MEMBER _read);
    W_PROPERTY(CustomWriteObject *,write MEMBER _write);
public:
    TypeLazyRegistration()
        : _read()
        , _write()
    {}
};

class EnumFlagsTester : public QObject
{
    W_OBJECT(EnumFlagsTester)
public:
    enum TestEnum { e1, e2 };
    W_ENUM(TestEnum, e1, e2);

    enum TestFlag { flag1 = 0x1, flag2 = 0x2 };
    W_DECLARE_FLAGS(TestFlags, TestFlag);

public:
    using QObject::QObject;

    TestEnum enumProperty() const { return m_enum; }
    void setEnumProperty(TestEnum e) { m_enum = e; }

    TestFlags flagProperty() const { return m_flags; }
    void setFlagProperty(TestFlags f) { m_flags = f; }

private:
    W_PROPERTY(TestEnum, enumProperty WRITE setEnumProperty READ enumProperty);
    W_PROPERTY(TestFlags, flagProperty WRITE setFlagProperty READ flagProperty);

private:
    TestEnum m_enum = e1;
    TestFlags m_flags;
};

W_OBJECT_IMPL(CustomReadObject)
W_OBJECT_IMPL(CustomWriteObject)
W_OBJECT_IMPL(CustomWriteObjectChild)
W_OBJECT_IMPL(TypeLazyRegistration)
W_OBJECT_IMPL(EnumFlagsTester)

Q_DECLARE_OPERATORS_FOR_FLAGS(EnumFlagsTester::TestFlags)

void tst_QMetaProperty::readAndWriteWithLazyRegistration()
{
    QVERIFY(!QMetaType::fromName("CustomReadObject*").isValid());
    QVERIFY(!QMetaType::fromName("CustomWriteObject*").isValid());

    TypeLazyRegistration o;
    QVERIFY(o.property("read").isValid());
    QVERIFY(QMetaType::fromName("CustomReadObject*").isValid());
    QVERIFY(!QMetaType::fromName("CustomWriteObject*").isValid());

    CustomWriteObjectChild data;
    QVariant value = QVariant::fromValue(&data); // this register CustomWriteObjectChild
    // check if base classes are not registered automatically, otherwise this test would be meaningless
    QVERIFY(!QMetaType::fromName("CustomWriteObject*").isValid());
    QVERIFY(o.setProperty("write", value));
    QVERIFY(QMetaType::fromName("CustomWriteObject*").isValid());
    QCOMPARE(o.property("write").value<CustomWriteObjectChild*>(), &data);
}

void tst_QMetaProperty::mapProperty()
{
    map.insert(5, 9);
    QVariant v1 = QVariant::fromValue(map);
    QVariant v = property("map");
    QVERIFY(v.isValid());
    QCOMPARE(map, (v.value<QMap<int,int> >()));
}

void tst_QMetaProperty::conversion()
{
    if (qVersion() < QByteArray("5.6.0"))
        QSKIP("this is a test for a bug in 5.5");


    QMetaType::registerConverter<QString, CustomType>();
    QMetaType::registerConverter<CustomType, QString>();

    QString hello = QStringLiteral("Hello");

    // Write to a QString property using a CustomType in a QVariant
    QMetaProperty value7P = metaObject()->property(metaObject()->indexOfProperty("value7"));
    QVERIFY(value7P.isValid());
    QVERIFY(value7P.write(this, QVariant::fromValue(CustomType(hello))));
    QCOMPARE(value7, hello);

    // Write to a CustomType property using a QString in a QVariant
    QMetaProperty customP = metaObject()->property(metaObject()->indexOfProperty("custom"));
    QVERIFY(customP.isValid());
    QVERIFY(customP.write(this, hello));
    QCOMPARE(custom.str, hello);

    // Something that cannot be converted should fail
    QVERIFY(!customP.write(this, 45));
    QVERIFY(!customP.write(this, QVariant::fromValue(this)));
    QVERIFY(!value7P.write(this, QVariant::fromValue(this)));
    QVERIFY(!value7P.write(this, QVariant::fromValue<QObject*>(this)));

    // none of this should have changed the values
    QCOMPARE(value7, hello);
    QCOMPARE(custom.str, hello);

    // Empty variant should be converted to default object
    QVERIFY(customP.write(this, QVariant()));
    QCOMPARE(custom.str, QString());
    // or reset resetable
    QVERIFY(value7P.write(this, QVariant()));
    QCOMPARE(value7, QLatin1String("reset"));
}

void tst_QMetaProperty::enumsFlags()
{
    // QTBUG-83689, verify that enumerations and flags can be assigned from int,
    // which is important for Qt Designer.
    EnumFlagsTester t;

    auto mo = t.metaObject();

    const int enumIndex = mo->indexOfProperty("enumProperty");
    QVERIFY(enumIndex >= 0);
    auto enumProperty = mo->property(enumIndex);
    QVERIFY(enumProperty.metaType().flags().testFlag(QMetaType::IsEnumeration));
    QVERIFY(enumProperty.write(&t, QVariant(int(EnumFlagsTester::e2))));
    QCOMPARE(t.enumProperty(), EnumFlagsTester::e2);

    const int flagsIndex = mo->indexOfProperty("flagProperty");
    QVERIFY(flagsIndex >= 0);
    auto flagsProperty = mo->property(flagsIndex);
    QVERIFY(flagsProperty.metaType().flags().testFlag(QMetaType::IsEnumeration));
    QVERIFY(flagsProperty.write(&t, QVariant(int(EnumFlagsTester::flag2))));
    QCOMPARE(t.flagProperty(), EnumFlagsTester::flag2);
}

QTEST_MAIN(tst_QMetaProperty)
