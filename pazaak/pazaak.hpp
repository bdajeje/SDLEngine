#ifndef PAZAAK_HPP
#define PAZAAK_HPP

#include "game/game.hpp"

namespace view {
  class MainMenu;
  class PlayMenu;
  class OptionMenu;
}

class Pazaak final : public Game
{
  public:

    Pazaak();

  protected:

    void newEvent( const SDL_Event& event );
    void showPlayMenu();
    void showOptionMenu();

  private:

    std::shared_ptr<view::MainMenu> m_main_menu;
    std::shared_ptr<view::PlayMenu> m_play_menu;
    std::shared_ptr<view::OptionMenu> m_option_menu;
};

#endif // PAZAAK_HPP
