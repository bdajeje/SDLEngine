#include "game.hpp"

#include "engine.hpp"
#include "utils/logging/easylogging++.h"

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
    }

    // Clear screen
    Engine::clearScreen();

    // Update screen
    Engine::render( m_current_view );
  }
}
