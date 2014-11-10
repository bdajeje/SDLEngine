#include "window.hpp"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "defines.hpp"
#include "utils/logging/easylogging++.h"

namespace graphics {

Window::Window(const std::string& title, int width, int height)
{
  // Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
  {
    LOG(ERROR) << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
    throw std::exception();
  }

  // Create window
  m_window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
  if( m_window == NULL )
  {
    LOG(ERROR) << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
    throw std::exception();
  }

  // Create renderer
  m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ); // SDL_RENDERER_PRESENTVSYNC (vertical sync) caps framerate on monitor
  if( m_renderer == NULL )
  {
    LOG(ERROR) << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
    throw std::exception();
  }

  // Initialize renderer color
  SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

  //Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) )
  {
    LOG(ERROR) << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << "\n";
    throw std::exception();
  }

  // Initialize SDL_ttf
  if( TTF_Init() == -1 )
  {
    LOG(ERROR) << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << "\n";
    throw std::exception();
  }

  // Initialize SDL_mixer
  if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
  {
    LOG(ERROR) << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
    throw std::exception();
  }
}

Window::~Window()
{
  // Destroy window
  SDL_DestroyRenderer( m_renderer );
  SDL_DestroyWindow( m_window );
}

void Window::clear()
{
  SDL_RenderClear( m_renderer );
}

void Window::render( graphics::ViewPtr view )
{
  if(!view)
  {
    LOG(ERROR) << "Can't render a NULL view!";
    return;
  }

  view->render( m_renderer );
  SDL_RenderPresent( m_renderer );
}

}
