#include "engine.hpp"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "graphics/manager/font_manager.hpp"
#include "graphics/manager/texture_manager.hpp"
#include "sounds/sounds_manager.hpp"
#include "utils/configuration/configurations.hpp"
#include "utils/logging/easylogging++.h"
#include "utils/translations.hpp"

std::unique_ptr<Engine> Engine::s_instance;
Events Engine::s_events;

void Engine::init(const std::string& title, int width, int height,
                  const std::string& configs_path, const std::vector<std::string>& config_files,
                  const std::string& translations_path, const std::string& language_file,
                  const std::string& images_path, const std::string& fonts_path,
                  const std::string& musics_path, const std::string& sounds_path)
{
  if( s_instance )
  {
    LOG(ERROR) << "Engine already initialized";
    return;
  }

  utils::Translations::init(translations_path, language_file);
  graphics::TextureManager::init(images_path);
  graphics::FontManager::init(fonts_path);
  sounds::SoundsManager::init(musics_path, sounds_path);

  // Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
  {
    LOG(ERROR) << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
    throw std::exception();
  }

  // Create window
  auto window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
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

  // Initialize events
  s_events.MenuSelectItem = SDL_RegisterEvents(1);

  s_instance.reset( new Engine(configs_path, config_files, window, renderer) );
}

Engine::Engine(const std::string& configs_path, const std::vector<std::string>& config_files, SDL_Window* window, SDL_Renderer* renderer)
  : m_configurations{ configs_path, config_files }
  , m_window{window}
  , m_renderer{renderer}
{
  try
  {
    // Apply last time used sound volume
    sounds::SoundsManager::setSoundVolume( std::stoi(m_configurations.get( config::sound::Volume )) );

    // Apply last time used music volume
    sounds::SoundsManager::setMusicVolume( std::stoi(m_configurations.get( config::music::Volume )) );
  }
  catch(const std::exception& e)
  {
    LOG(ERROR) << "Bad engine configurations: " << e.what();
  }
}

void Engine::clean()
{
  graphics::TextureManager::clean();
  graphics::FontManager::clean();
  sounds::SoundsManager::clean();

  SDL_DestroyRenderer( s_instance->m_renderer );
  SDL_DestroyWindow( s_instance->m_window );
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

  view->render();
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
