#-------------------------------------------------
#
# Project created by QtCreator 2012-12-19T10:04:29
#
#-------------------------------------------------

QT       += core gui network

TARGET = Game
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    mygraphicsview.cpp

HEADERS  += mainwindow.h \
    scene.h \
    mygraphicsview.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    Smile.png \
    secondPlayerBase.jpg \
    secondHero.png \
    mapGrassDeny.jpg \
    mapGrassAllow.jpg \
    mapGrass.jpg \
    firstPlayerBase.jpg \
    firstHero.png \
    bg.jpg \
    Map.txt
