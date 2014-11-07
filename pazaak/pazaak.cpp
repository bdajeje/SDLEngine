#include "pazaak.hpp"

#include "pazaak/views/main_menu.hpp"

Pazaak::Pazaak(const utils::Configuration& configs, int width, int height)
  : Game{configs, "Pazaak", width, height}
{
  m_main_menu = std::make_shared<view::MainMenu>(window().renderer(), graphics::Size{width, height});

  setCurrentView(m_main_menu);
}
