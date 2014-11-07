#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL_image.h>

#include "graphics/view.hpp"

class Game
{
  public:

    Game() = default;

    void draw(SDL_Renderer* renderer);

    void setCurrentView(graphics::ViewPtr view) { m_current_view = view; }

  private:

    graphics::ViewPtr m_current_view;
};

#endif // GAME_HPP
