CONFIG += testcase
qtConfig(c++20): CONFIG += c++20
TARGET = tst_qmetaobject
QT = core testlib
HEADERS = forwarddeclared.h
SOURCES = forwarddeclared.cpp tst_qmetaobject6.cpp
include(../../../src/verdigris.pri)
