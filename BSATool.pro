#-------------------------------------------------
#
# Project created by QtCreator 2014-07-31T13:22:43
#
#-------------------------------------------------

QT += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

test {
    QT += testlib

    TARGET = BSAToolTest
    TEMPLATE = app
    VERSION = 2.0

    CONFIG += c++14

    include(BSATool.pri)
    include(test/BSAToolTest.pri)
}
else {
    TARGET = BSATool
    TEMPLATE = app
    VERSION = 2.0

    CONFIG += c++14

    include(BSATool.pri)
    SOURCES += $$files(src/main/*.cpp, true)
}
