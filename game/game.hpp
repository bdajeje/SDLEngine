#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL_image.h>

#include "graphics/view.hpp"
#include "graphics/window.hpp"

class Game
{
  public:

    Game(const std::string& title, int width, int height);

    void run();

  protected:

    void setCurrentView(graphics::ViewPtr view) { m_current_view = view; }

    graphics::Window& window() { return m_window; }

  private:

    graphics::Window m_window;
    graphics::ViewPtr m_current_view;
};

#endif // GAME_HPP
