#ifndef PAZAAK_HPP
#define PAZAAK_HPP

#include "game.hpp"

class MainMenu;

class Pazaak final: public Game
{
  public:

    Pazaak();

  private:

    std::shared_ptr<MainMenu> m_main_menu;
};

#endif // PAZAAK_HPP
