#include "pazaak.hpp"

#include "engine.hpp" // \todo to remove

#include "pazaak/views/main_menu.hpp"

Pazaak::Pazaak()
{
  m_main_menu = std::make_shared<view::MainMenu>(Engine::windowSize());

  setCurrentView(m_main_menu);
}

void Pazaak::event(const SDL_Event &/*event*/)
{
  // \todo on escape key always show menu
}
