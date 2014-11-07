#include <SDL2/SDL.h>

#include "graphics/manager/texture_manager.hpp"
#include "pazaak/pazaak.hpp"
#include "utils/arguments/arguments.hpp"
#include "utils/configuration/configuration.hpp"
#include "utils/logging/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

enum Argument : short {
  WINDOW_WIDTH = 1, WINDOW_HEIGHT
};

int main( int argc, char* argv[] )
{
  // Mandatory init
  graphics::TextureManager::init("resources/images/");

  // Parse args
  auto args = utils::Arguments{argc, argv};

  // Read configurations
  auto configs = utils::Configuration{"resources/configurations/", {"sounds"} };

  // Start game
  auto pazaak = std::make_shared<Pazaak>(configs, args.get(WINDOW_WIDTH, 800), args.get(WINDOW_HEIGHT, 600));
  pazaak->run();

  // Quit
  IMG_Quit();
  SDL_Quit();

  return EXIT_SUCCESS;
}
