#ifndef PAZAAK_HPP
#define PAZAAK_HPP

#include "game/game.hpp"

namespace view {
  class MainMenu;
}

class Pazaak final: public Game
{
  public:

    Pazaak();

  private:

    std::shared_ptr<view::MainMenu> m_main_menu;
};

#endif // PAZAAK_HPP
