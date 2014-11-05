#include "window.hpp"

#include <SDL2/SDL_image.h>

#include "utils/logging/easylogging++.h"

namespace graphics {

SDL_Window* Window::s_window;
SDL_Surface* Window::s_screen;

void Window::init(const std::string& title, int width, int height)
{
  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    LOG(ERROR) << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
    throw;
  }

  //Create window
  s_window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
  if( s_window == NULL )
  {
    LOG(ERROR) << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
    throw;
  }

  //Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) )
  {
    LOG(ERROR) << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << "\n";
    throw;
  }

  //Get window surface
  s_screen = SDL_GetWindowSurface( s_window );
}

Window::~Window()
{
  // Destroy screen
  SDL_FreeSurface( s_screen );

  // Destroy window
  SDL_DestroyWindow( s_window );
}

bool Window::run(std::shared_ptr<Game> game)
{
  //Main loop flag
  bool quit    = false;
  bool success = true;

  //Event handler
  SDL_Event event;

  //Handle events on queue
  while( !quit )
  {
    while( SDL_PollEvent( &event ) != 0 )
    {
      //User requests quit
      if( event.type == SDL_QUIT )
        quit = true;

      //Fill the surface white
      SDL_FillRect( s_screen, NULL, SDL_MapRGB( s_screen->format, 0x00, 0x00, 0x00 ) );

      game->draw();

      //Update the surface
      SDL_UpdateWindowSurface( s_window );
    }
  }

  return success;
}

}
