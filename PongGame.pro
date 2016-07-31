TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# Flags
QMAKE_CXXFLAGS += -Wall -Wextra -std=c++0x

# Optimization flags depends on the build type.
CONFIG(debug, debug|release)
{
    win32 {
        DESTDIR = $$PWD/out/windows/debug-build
    }
    unix {
        DESTDIR = $$PWD/out/linux/debug-build
    }

    OBJECTS_DIR = $$DESTDIR/obj
    QMAKE_CXXFLAGS += -O0
}

CONFIG(release, release|debug)
{

    win32 {
        DESTDIR = $$PWD/out/windows/release-build
    }
    unix {
        DESTDIR = $$PWD/out/linux/release-build
    }

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
    src/window.cpp \
    src/game.cpp \
    src/font_manager.cpp \
    src/font.cpp \
    src/audio.cpp \
    src/texture.cpp \
    src/vector2d.cpp \
    src/random.cpp \
    src/image.cpp

HEADERS += \
    src/paddle.hpp \
    src/ball.hpp \
    src/window.hpp \
    src/game.hpp \
    src/font_manager.hpp \
    src/font.hpp \
    src/audio.hpp \
    src/texture.hpp \
    src/vector2d.hpp \
    src/random.hpp \
    src/debug.hpp \
    src/image.hpp

DISTFILES += \
    makefile

