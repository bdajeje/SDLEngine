#include "pazaak.hpp"
#include "pazaak/views/main_menu.hpp"
#include "pazaak/views/play_menu.hpp"
#include "pazaak/views/option_menu.hpp"

#include "engine.hpp"

Pazaak::Pazaak()
{
  m_main_menu = std::make_shared<view::MainMenu>(Engine::windowSize());

  setCurrentView(m_main_menu);
}

void Pazaak::newEvent(const SDL_Event &event)
{
  // Always calls Game::newEvent to handle common game events
  // \todo decorator pattern to avoid having to call this?
  Game::newEvent(event);

  if( event.type == Engine::events().MenuSelectItem && m_current_view == m_main_menu )
  {
    // \todo I hate those hardcoded numbers, do something about it!
    switch( m_main_menu->selectedPosition() )
    {
      case 0:
        showPlayMenu(); break;
      case 2:
        showOptionMenu(); break;
      case 3:
        quit(); break;
    }
  }
}

void Pazaak::showPlayMenu()
{
  if(!m_play_menu)
  {
    m_play_menu = std::make_shared<view::PlayMenu>(Engine::windowSize());
    m_play_menu->setPreviousView( m_main_menu );
  }

  setCurrentView(m_play_menu);
}


void Pazaak::showOptionMenu()
{
  if(!m_option_menu)
  {
    m_option_menu = std::make_shared<view::OptionMenu>(Engine::windowSize());
    m_option_menu->setPreviousView( m_main_menu );
  }

  setCurrentView(m_option_menu);
}
