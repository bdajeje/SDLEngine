TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    window.cpp \
    game.cpp \
    pazaak/pazaak.cpp \
    view.cpp \
    pazaak/views/main_menu.cpp \
    drawable.cpp

LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    window.hpp \
    defines.hpp \
    game.hpp \
    pazaak/pazaak.hpp \
    view.hpp \
    pazaak/surfaces.hpp \
    pazaak/views/main_menu.hpp \
    drawable.hpp
