#include "engine.hpp"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "utils/configuration/configurations.hpp"
#include "utils/logging/easylogging++.h"

std::unique_ptr<Engine> Engine::s_instance;

void Engine::init(const EngineConfiguration& configurations)
{
  // Don't initialize twice
  if( s_instance )
  {
    LOG(ERROR) << "Engine already initialized";
    return;
  }

  // Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
  {
    LOG(ERROR) << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
    throw std::exception();
  }

  // Create window
  auto window = SDL_CreateWindow( configurations.title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  configurations.size.w, configurations.size.h, SDL_WINDOW_SHOWN );
  if( window == NULL )
  {
    LOG(ERROR) << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
    throw std::exception();
  }

  // Create renderer
  auto renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ); // SDL_RENDERER_PRESENTVSYNC (vertical sync) caps framerate on monitor
  if( renderer == NULL )
  {
    LOG(ERROR) << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
    throw std::exception();
  }

  // Initialize renderer color
  SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

  // Initialize PNG loading
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

  s_instance.reset( new Engine(configurations, window, renderer) );
}

Engine::Engine(const EngineConfiguration& configurations, SDL_Window* window, SDL_Renderer* renderer)
  : m_configurations {configurations.configs_path}
  , m_translations_manager {configurations.translations_path, m_configurations.get(config::translation::Language)}
  , m_textures_manager {configurations.images_path}
  , m_fonts_manager {configurations.fonts_path}
  , m_sounds_manager {configurations.musics_path, configurations.sounds_path}
  , m_window {window}
  , m_renderer {renderer}
{
  try
  {
    // Apply last time used sound volume
    m_sounds_manager.setSoundVolume( std::stoi(m_configurations.get( config::sound::Volume )) );

    // Apply last time used music volume
    m_sounds_manager.setMusicVolume( std::stoi(m_configurations.get( config::music::Volume )) );
  }
  catch(const std::exception& e)
  {
    LOG(ERROR) << "Bad engine configurations: " << e.what();
  }

  // Initialize events
  m_events.MenuSelectItem = SDL_RegisterEvents(1);
  m_events.PreviousView   = SDL_RegisterEvents(1);
}

void Engine::clean()
{
  SDL_DestroyRenderer( s_instance->m_renderer );
  SDL_DestroyWindow( s_instance->m_window );

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void Engine::clearScreen()
{
  SDL_RenderClear( s_instance->m_renderer );
}

void Engine::render( graphics::ViewPtr view )
{
  if(!view)
  {
    LOG(ERROR) << "Can't render a NULL view!";
    return;
  }

  view->draw();
  SDL_RenderPresent( s_instance->m_renderer );
}

graphics::Size Engine::windowSize()
{
  int width, height;
  SDL_GetWindowSize( s_instance->m_window, &width, &height );
  return {width, height};
}

graphics::Position Engine::mousePosition()
{
  graphics::Position position;
  SDL_GetMouseState( &position.x, &position.y );
  return position;
}

