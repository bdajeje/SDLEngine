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

  // Init the game engine
  EngineConfiguration configs {"Pazaak", "resources/configurations/", "resources/translations/", "resources/images/",
                               "resources/fonts/", "resources/musics/", "resources/sounds/",
                               graphics::Size{args.get<int>(WINDOW_WIDTH, 800), args.get<int>(WINDOW_HEIGHT, 600)} };
  Engine::init(configs);

  // Start game
  Pazaak pazaak;
  pazaak.run();

  // Quit
  Engine::clean();

  return EXIT_SUCCESS;
}
