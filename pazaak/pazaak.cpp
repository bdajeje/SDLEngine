#include "pazaak.hpp"

#include "pazaak/views/main_menu.hpp"

Pazaak::Pazaak()
{
  m_main_menu = std::make_shared<view::MainMenu>();

  setCurrentView(m_main_menu);
}
