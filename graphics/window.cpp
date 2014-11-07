#include "window.hpp"

#include <SDL2/SDL_image.h>

#include "utils/logging/easylogging++.h"

namespace graphics {

Window::Window(const std::string& title, int width, int height)
{
  // Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    LOG(ERROR) << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
    throw;
  }

  // Create window
  m_window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
  if( m_window == NULL )
  {
    LOG(ERROR) << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
    throw;
  }

  // Create renderer
  m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );
  if( m_renderer == NULL )
  {
    LOG(ERROR) << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
    throw;
  }

  // Initialize renderer color
  SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

  //Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) )
  {
    LOG(ERROR) << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << "\n";
    throw;
  }
}

Window::~Window()
{
  // Destroy window
  SDL_DestroyRenderer( m_renderer );
  SDL_DestroyWindow( m_window );
}

bool Window::run(std::shared_ptr<Game> game)
{
  bool quit = false;
  SDL_Event event;

  // Handle events on queue
  while( !quit )
  {
    while( SDL_PollEvent( &event ) != 0 )
    {
      // User requests quit
      if( event.type == SDL_QUIT )
        quit = true;

      // Clear screen
      SDL_RenderClear( m_renderer );

      // Let the game draw its things
      game->draw(m_renderer);

      // Update screen
      SDL_RenderPresent( m_renderer );
    }
  }

  return true;
}

}
