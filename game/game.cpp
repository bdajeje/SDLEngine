#include "game.hpp"

#include "utils/logging/easylogging++.h"

Game::Game(const utils::Configuration& configs, const std::string& title, int width, int height)
  : m_configurations(configs)
  , m_window(title, width, height)
{}

void Game::run()
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
      m_window.clear();

      // Update screen
      if(m_current_view)
        m_window.render( m_current_view );
      else
        LOG(ERROR) << "Game with no current view!";
    }
  }
}
