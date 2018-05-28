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

# 增加预编译头，提升二次编译的速度
PRECOMPILED_HEADER = stable.h


SOURCES += main.cpp\
    helper/attribution.cpp \
    helper/clickablelabel.cpp \
    helper/cogmodel.cpp \
    initial.cpp \
    knowledge.cpp \
    login.cpp \
    helper/mypushbutton.cpp \
    helper/node.cpp \
    registor.cpp \
    teach.cpp \
    test.cpp \
    usecase.cpp \
    helper/user.cpp \
    userinfowidget.cpp \
    helper/patterntest.cpp

HEADERS  += \
    helper/attribution.h \
    helper/clickablelabel.h \
    helper/myheaders.h \
    helper/cogmodel.h \
    initial.h \
    knowledge.h \
    login.h \
    helper/mypushbutton.h \
    helper/node.h \
    registor.h \
    teach.h \
    test.h \
    usecase.h \
    helper/user.h \
    userinfowidget.h \
    stable.h \
    helper/patterntest.h

FORMS    += \
    helper/attribution.ui \
    initial.ui \
    knowledge.ui \
    registor.ui \
    teach.ui \
    test.ui \
    usecase.ui \
    login.ui \
    userinfowidget.ui \
    helper/patterntest.ui

# CONFIG += qaxcontainer  为了使dynamicCall等  ActiveQt\qaxwidget.h 下的相关文件有效

CONFIG += C++11 qaxcontainer

RESOURCES += \
    educationsystem.qrc

RC_FILE = education.rc

DISTFILES += \
    education.rc


