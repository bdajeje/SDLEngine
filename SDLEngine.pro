TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    game/game.cpp \
    pazaak/pazaak.cpp \
    graphics/view.cpp \
    pazaak/views/main_menu.cpp \
    graphics/drawable.cpp \
    graphics/manager/texture_manager.cpp \
    utils/arguments/arguments.cpp \
    utils/configuration/configuration.cpp \
    utils/files.cpp \
    graphics/animation.cpp \
    sounds/sounds_manager.cpp \
    graphics/text.cpp \
    graphics/manager/font_manager.cpp \
    utils/translations.cpp \
    graphics/vlayout.cpp \
    graphics/layout.cpp \
    engine.cpp \
    graphics/menu.cpp \
    pazaak/views/play_menu.cpp \
    pazaak/views/option_menu.cpp \
    pazaak/views/pazaak_menu.cpp

LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lboost_filesystem -lboost_system

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
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
    graphics/animation.hpp \
    sounds/sounds_manager.hpp \
    graphics/text.hpp \
    graphics/manager/font_manager.hpp \
    utils/translations.hpp \
    pazaak/translations.hpp \
    graphics/vlayout.hpp \
    graphics/layout.hpp \
    engine.hpp \
    graphics/menu.hpp \
    pazaak/sounds.hpp \
    pazaak/musics.hpp \
    utils/configuration/configurations.hpp \
    pazaak/views/play_menu.hpp \
    pazaak/views/option_menu.hpp \
    pazaak/views/pazaak_menu.hpp
