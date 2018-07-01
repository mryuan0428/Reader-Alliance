#-------------------------------------------------
#
# Project created by QtCreator 2018-05-27T16:56:56
#
#-------------------------------------------------

QT       += core gui sql
RC_ICONS = ra_ico.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ra
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    ra_mainwindow.cpp \
    ra_bookinfo.cpp \
    ra_login.cpp \
    ra_mainwindow_user.cpp \
    ra_mainwindow_user.cpp \
    ra_mainwindow_admin.cpp \
    ra_register.cpp \
    ra_activity.cpp \
    ra_sharebook.cpp \
    ra_bookreview.cpp \
    ra_addactivity.cpp \
    ra_usercenter.cpp \
    ra_regman.cpp \
    ra_bookman.cpp \
    ra_activityman.cpp \
    ra_userman.cpp

HEADERS += \
        ra_mainwindow.h \
    ra_bookinfo.h \
    ra_login.h \
    ra_mainwindow_user.h \
    ra_mainwindow_admin.h \
    ra_register.h \
    ra_activity.h \
    ra_sharebook.h \
    ra_bookreview.h \
    ra_addactivity.h \
    ra_usercenter.h \
    ra_regman.h \
    ra_bookman.h \
    ra_activityman.h \
    ra_userman.h

FORMS += \
        ra_mainwindow.ui \
    ra_bookinfo.ui \
    ra_login.ui \
    ra_mainwindow_user.ui \
    ra_mainwindow_admin.ui \
    ra_register.ui \
    ra_activity.ui \
    ra_sharebook.ui \
    ra_bookreview.ui \
    ra_addactivity.ui \
    ra_usercenter.ui \
    ra_regman.ui \
    ra_bookman.ui \
    ra_activityman.ui \
    ra_userman.ui

RESOURCES += \
    img.qrc
