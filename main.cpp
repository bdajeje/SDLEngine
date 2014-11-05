#include <SDL2/SDL.h>
#include <iostream>

#include "utils/logging/easylogging++.h"
#include "graphics/window.hpp"
#include "pazaak/pazaak.hpp"

_INITIALIZE_EASYLOGGINGPP

int main( /*int argc, char* args[]*/ )
{
  graphics::Window::init("Pazaak", 800, 600);
  graphics::Window::run( std::make_shared<Pazaak>() );

  SDL_Quit();

  return 0;
}
