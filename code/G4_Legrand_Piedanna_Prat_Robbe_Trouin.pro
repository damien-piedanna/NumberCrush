TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -static

SOURCES += main.cpp \
    Correc_prof/gridmanagement.cpp \
    Correc_prof/nsutil.cpp \
    Correc_prof/game.cpp \
    Correc_prof/params.cpp \
    Nos_fichiers/scores.cpp \
    Nos_fichiers/menu.cpp \
    Nos_fichiers/gridmanage.cpp \
    Nos_fichiers/consolemanagement.cpp \
    Nos_fichiers/move.cpp \
    Nos_fichiers/jeu.cpp \
    Nos_fichiers/params2.cpp \
    Nos_fichiers/useractions.cpp \
    Nos_fichiers/creator.cpp

HEADERS += \
    Correc_prof/nsutil.h \
    Correc_prof/type.h \
    Correc_prof/params.h \
    Correc_prof/gridmanagement.h \
    Correc_prof/game.h \
    Nos_fichiers/scores.h \
    Nos_fichiers/menu.h \
    Nos_fichiers/gridmanage.h \
    Nos_fichiers/consolemanagement.h \
    Nos_fichiers/jeu.h \
    Nos_fichiers/params2.h \
    Nos_fichiers/move.h \
    Nos_fichiers/useractions.h \
    Nos_fichiers/creator.h


QMAKE_MAC_SDK = macosx10.13
