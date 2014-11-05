TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    graphics/window.cpp \
    game/game.cpp \
    pazaak/pazaak.cpp \
    graphics/view.cpp \
    pazaak/views/main_menu.cpp \
    graphics/drawable.cpp

LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    graphics/window.hpp \
    defines.hpp \
    game/game.hpp \
    pazaak/pazaak.hpp \
    graphics/view.hpp \
    pazaak/surfaces.hpp \
    pazaak/views/main_menu.hpp \
    graphics/drawable.hpp
