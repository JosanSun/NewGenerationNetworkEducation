#-------------------------------------------------
#
# Project created by QtCreator 2017-08-27T22:15:23
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PatternKnowledgeEducationSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    administrate.cpp \
    attribution.cpp \
    clickablelabel.cpp \
    cogmodel.cpp \
    initial.cpp \
    knowledge.cpp \
    login.cpp \
    mypushbutton.cpp \
    node.cpp \
    registor.cpp \
    teach.cpp \
    test.cpp \
    usecase.cpp \
    user.cpp

HEADERS  += \
    administrate.h \
    attribution.h \
    clickablelabel.h \
    cogmodel.h \
    initial.h \
    knowledge.h \
    login.h \
    mypushbutton.h \
    node.h \
    registor.h \
    resource.h \
    teach.h \
    test.h \
    usecase.h \
    user.h

FORMS    += \
    administrate.ui \
    attribution.ui \
    initial.ui \
    knowledge.ui \
    registor.ui \
    teach.ui \
    test.ui \
    usecase.ui \
    login.ui

# CONFIG += qaxcontainer  为了使dynamicCall等  ActiveQt\qaxwidget.h 下的相关文件有效

CONFIG += C++11 qaxcontainer

RESOURCES += \
    educationsystem.qrc
