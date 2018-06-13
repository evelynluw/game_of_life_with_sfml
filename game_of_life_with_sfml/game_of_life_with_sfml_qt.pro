TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    game_of_life.cpp \
    game_of_life_sfml.cpp \
    sidebar.cpp \
    animate.cpp

#LIBS += -L"..\..\SFML-2.0\lib" #change this
#LIBS += -L"..\..\SFML-2.0\bin" #change this
LIBS += -L"D:\SFML-2.5.0\lib" #change this
LIBS += -L"D:\SFML-2.5.0\bin" #change this

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

#INCLUDEPATH += "..\..\SFML-2.0\include" #change this
#DEPENDPATH += "..\..\SFML-2.0\include" #change this
INCLUDEPATH += "D:\SFML-2.5.0\include" #change this
DEPENDPATH += "D:\SFML-2.5.0\include" #change this

HEADERS += \
    game_of_life.h \
    game_of_life_sfml.h \
    constants.h \
    sidebar.h \
    animate.h

DISTFILES += \
    notes.txt \
    test.md
