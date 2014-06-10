TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

#Flags
QMAKE_CXXFLAGS +=   -std=c++11 \
                    -O0 #-O0 for 0 level of optimization and better debugging.

#Windows Config.
win32 {
INCLUDEPATH += "C:\SDL2\i686-w64-mingw32\include"
LIBS += -L"C:\SDL2\i686-w64-mingw32\lib"

LIBS += -lmingw32       \
        -lSDL2main      \
        -lSDL2          \
        -lSDL2_ttf      \
        -lSDL2_image    \
        -lSDL2_mixer    \
        -static-libgcc
}

#Linux like config.
LIBS+= -lSDL2 \
       -lSDL2_image \
       -lSDL2_ttf \
       -lSDL2_mixer

SOURCES += main.cpp \
    paddle.cpp \
    ball.cpp \
    utils.cpp \
    pong.cpp \
    debug.cpp \
    sdl_audio.cpp

HEADERS += \
    utils.hpp \
    paddle.hpp \
    ball.hpp \
    pong.hpp \
    debug.hpp \
    sdl_audio.h

