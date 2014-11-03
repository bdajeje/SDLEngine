#include <SDL2/SDL.h>
#include <iostream>

#include "utils/logging/easylogging++.h"
#include "window.hpp"
#include "pazaak/pazaak.hpp"

_INITIALIZE_EASYLOGGINGPP

int main( /*int argc, char* args[]*/ )
{
  Window::init("Pazaak", 800, 600);

  Window::run( std::make_shared<Pazaak>() );

  //Quit SDL subsystems
  SDL_Quit();

  return 0;
}
