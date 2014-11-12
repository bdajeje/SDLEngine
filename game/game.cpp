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

      // Let child class do whatevere it wants with events
      newEvent( event );

      // Give event to the current view
      m_current_view->newEvent( event );
    }

    // Clear screen
    Engine::clearScreen();

    // Update screen
    Engine::render( m_current_view );
  }
}
