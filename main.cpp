#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "engine.hpp"
#include "utils/arguments/arguments.hpp"
#include "utils/logging/easylogging++.h"

#include "pazaak/pazaak.hpp"

_INITIALIZE_EASYLOGGINGPP

enum Argument : short {
  WINDOW_WIDTH = 1, WINDOW_HEIGHT
};

int main( int argc, char* argv[] )
{
  // Parse args
  auto args = utils::Arguments{argc, argv};

  // Init the engine
  Engine::init ( "Pazaak", args.get(WINDOW_WIDTH, 800), args.get(WINDOW_HEIGHT, 600),
                 "resources/configurations/", std::vector<std::string>{"configurations"},
                 "resources/translations/", "en",
                 "resources/images/", "resources/fonts/",
                 "resources/musics/", "resources/sounds/"
                );

  // Start game
  Pazaak pazaak;
  pazaak.run();

  // Quit
  Engine::clean();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  return EXIT_SUCCESS;
}
