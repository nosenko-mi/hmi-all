QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chartwidget.cpp \
    fileutils.cpp \
    inpututils.cpp \
    main.cpp \
    mainwindow.cpp \
    mathutils.cpp \
    point.cpp \
    pointsserializer.cpp \
    renderarea.cpp \
    tablewindow.cpp

HEADERS += \
    chartwidget.h \
    fileutils.h \
    inpututils.h \
    mainwindow.h \
    mathutils.h \
    point.h \
    pointsserializer.h \
    renderarea.h \
    tablewindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
