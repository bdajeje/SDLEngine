#include <SDL2/SDL.h>

#include "graphics/manager/font_manager.hpp"
#include "graphics/manager/texture_manager.hpp"
#include "pazaak/pazaak.hpp"
#include "sounds/sounds_manager.hpp"
#include "utils/arguments/arguments.hpp"
#include "utils/configuration/configuration.hpp"
#include "utils/logging/easylogging++.h"
#include "utils/translations.hpp"

_INITIALIZE_EASYLOGGINGPP

enum Argument : short {
  WINDOW_WIDTH = 1, WINDOW_HEIGHT
};

int main( int argc, char* argv[] )
{
  // Mandatory init
  utils::Translations::init("resources/translations/", "en");
  graphics::TextureManager::init("resources/images/");
  graphics::FontManager::init("resources/fonts/");
  sounds::SoundsManager::init("resources/musics/", "resources/sounds/");

  // Parse args
  auto args = utils::Arguments{argc, argv};

  // Read configurations
  auto configs = utils::Configuration{"resources/configurations/", {"sounds"} };

  // Start game
  auto pazaak = std::make_shared<Pazaak>(configs, args.get(WINDOW_WIDTH, 800), args.get(WINDOW_HEIGHT, 600));
  pazaak->run();

  // We need to clean resources before SDL quit
  graphics::TextureManager::clean();
  graphics::FontManager::clean();
  sounds::SoundsManager::clean();

  // Quit
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  return EXIT_SUCCESS;
}
