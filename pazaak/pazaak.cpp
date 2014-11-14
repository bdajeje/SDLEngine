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
  // \todo on escape key always show menu (except if current_view is the menu)
  if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE )
  {
    if( m_current_view == m_main_menu )
      m_main_menu->setFocusToPosition(2);
    else
      setCurrentView(m_main_menu);

    return;
  }

  if( event.type == Engine::events().MenuSelectItem && m_current_view == m_main_menu )
  {
    switch( m_main_menu->selectedPosition() )
    {
      case 0:
        showPlayMenu(); break;
      case 1:
        showOptionMenu(); break;
      case 2:
        quit(); break;
    }
  }
}

void Pazaak::showPlayMenu()
{
  if(!m_play_menu)
    m_play_menu = std::make_shared<view::PlayMenu>(Engine::windowSize());

  setCurrentView(m_play_menu);
}


void Pazaak::showOptionMenu()
{
  if(!m_option_menu)
    m_option_menu = std::make_shared<view::OptionMenu>(Engine::windowSize());

  setCurrentView(m_option_menu);
}
