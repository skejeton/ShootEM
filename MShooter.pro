#-------------------------------------------------
#
# Project created by QtCreator 2018-11-18T22:52:31
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MShooter
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++14
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    player.cpp \
    gamedata.cpp \
    map.cpp \
    mapobject.cpp \
    background.cpp \
    camera.cpp \
    weapon.cpp \
    weaponpart.cpp \
    leafshieldweapon.cpp \
    liveshud.cpp \
    cooldown.cpp \
    animation.tpp \
    entity.cpp \
    animationmanager.tpp \
    particle.cpp \
    faketext.cpp \
    dialog.cpp

HEADERS += \
        widget.h \
    player.h \
    gamedata.h \
    map.h \
    mapobject.h \
    background.h \
    camera.h \
    weapon.h \
    weaponpart.h \
    leafshieldweapon.h \
    allweapons.h \
    liveshud.h \
    cooldown.h \
    animation.h \
    entity.h \
    animationmanager.h \
    particle.h \
    faketext.h \
    dialog.h

FORMS += \
        widget.ui

RESOURCES += \
    resources.qrc
