#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL_image.h>

#include "view.hpp"

class Game
{
  public:

    Game();

    void draw();

    void setCurrentView(ViewPtr view) { m_current_view = view; }

  private:

    ViewPtr m_current_view;
};

#endif // GAME_HPP
