#include <SDL2/SDL.h>
#include <iostream>

#include "utils/logging/easylogging++.h"
#include "graphics/window.hpp"
#include "pazaak/pazaak.hpp"

_INITIALIZE_EASYLOGGINGPP

int main( /*int argc, char* args[]*/ )
{
  // \todo window size from args

  auto window = graphics::Window("Pazaak", 800, 600);
  window.run( std::make_shared<Pazaak>() );

  IMG_Quit();
  SDL_Quit();

  return 0;
}
