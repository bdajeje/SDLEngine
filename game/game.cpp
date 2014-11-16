#include "game.hpp"

#include "engine.hpp"
#include "utils/logging/easylogging++.h"

void Game::run()
{
  SDL_Event event;

  // Handle events on queue
  while( !m_quit )
  {
    while( SDL_PollEvent( &event ) != 0 )
    {
      // User requests quit
      if( event.type == SDL_QUIT )
        m_quit = true;

      // Handles events
      newEvent( event );
    }

    // Clear screen
    Engine::clearScreen();

    // Update screen
    Engine::render( m_current_view );
  }
}

void Game::newEvent( const SDL_Event& event)
{
  if( event.type == SDL_KEYDOWN )
  {
    // If the current view handled this event, stop propagation
    if( m_current_view->KeyboardEventBinder::send(event.key.keysym.sym) )
      return;
  }

  // Set previous view
  if( event.type == Engine::events().PreviousView && m_current_view->previousView() )
    m_current_view = m_current_view->previousView();
}
