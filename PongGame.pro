TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# Flags
QMAKE_CXXFLAGS +=   -std=c++11

# Optimization flags depends on the build type.
CONFIG(debug, debug|release)
{
    DESTDIR = $$OUT_PWD
    OBJECTS_DIR = $$DESTDIR/obj
    QMAKE_CXXFLAGS += -O0
}
CONFIG(release, release|debug)
{
    DESTDIR = $$OUT_PWD
    OBJECTS_DIR = $$DESTDIR/obj
    QMAKE_CXXFLAGS += -O3
}

# Windows config.
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

# Linux config.
unix {
LIBS+= -lSDL2 \
       -lSDL2_image \
       -lSDL2_ttf \
       -lSDL2_mixer
}

SOURCES += src/main.cpp \
    src/paddle.cpp \
    src/ball.cpp \
    src/utils.cpp \
    src/debug.cpp \
    src/ai.cpp \
    src/window.cpp \
    src/game.cpp \
    src/font_manager.cpp \
    src/font.cpp \
    src/audio.cpp \
    src/texture.cpp \
    src/vector2d.cpp

HEADERS += \
    src/utils.hpp \
    src/paddle.hpp \
    src/ball.hpp \
    src/debug.hpp \
    src/ai.hpp \
    src/window.hpp \
    src/game.hpp \
    src/font_manager.hpp \
    src/font.hpp \
    src/audio.hpp \
    src/texture.hpp \
    src/vector2d.hpp

