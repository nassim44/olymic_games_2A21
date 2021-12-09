#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql network  multimedia multimediawidgets
QT       += core gui charts #-----satistiques
QT       += core gui axcontainer


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets

TARGET = Atelier_Connexion
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

CONFIG += c++11

SOURCES += \
    admin.cpp \
    affecterjoueur.cpp \
    event.cpp \
    gestion_des_jeux.cpp \
    gestion_des_joueurs.cpp \
    gestion_des_stades.cpp \
    historique.cpp \
    joueur.cpp \
    location.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    olympic_games.cpp \
    smtp.cpp \
    stade.cpp \
    statj.cpp

HEADERS += \
    admin.h \
    affecterjoueur.h \
    event.h \
    gestion_des_jeux.h \
    gestion_des_joueurs.h \
    gestion_des_stades.h \
    historique.h \
    joueur.h \
    location.h \
        mainwindow.h \
    connection.h \
    olympic_games.h \
    olympic_games.h \
    smtp.h \
    stade.h \
    statj.h

FORMS += \
        admin.ui \
        gestion_des_jeux.ui \
        gestion_des_joueurs.ui \
        gestion_des_stades.ui \
        mainwindow.ui \
        statj.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc
