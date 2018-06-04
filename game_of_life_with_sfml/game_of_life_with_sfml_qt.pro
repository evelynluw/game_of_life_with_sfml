TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    game_of_life.cpp

LIBS += -L"..\..\SFML-2.0\lib" #change this
LIBS += -L"..\..\SFML-2.0\bin" #change this

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

INCLUDEPATH += "..\..\SFML-2.0\include" #change this
DEPENDPATH += "..\..\SFML-2.0\include" #change this

HEADERS += \
    game_of_life.h \
    constants.h
