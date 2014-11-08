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
    graphics/drawable.cpp \
    graphics/manager/texture_manager.cpp \
    utils/arguments/arguments.cpp \
    utils/configuration/configuration.cpp \
    utils/files.cpp \
    graphics/animation.cpp

LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lboost_filesystem -lboost_system

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    graphics/window.hpp \
    defines.hpp \
    game/game.hpp \
    pazaak/pazaak.hpp \
    graphics/view.hpp \
    pazaak/views/main_menu.hpp \
    graphics/drawable.hpp \
    pazaak/textures.hpp \
    graphics/manager/texture_manager.hpp \
    utils/arguments/arguments.hpp \
    graphics/position.hpp \
    graphics/size.hpp \
    utils/configuration/configuration.hpp \
    utils/files.hpp \
    graphics/animation.hpp
