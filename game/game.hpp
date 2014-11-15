#ifndef GAME_HPP
#define GAME_HPP

#include "graphics/view.hpp"

class Game
{
  public:

    void run();
    void quit() { m_quit = true; }

  protected:

    void setCurrentView(graphics::ViewPtr view) { m_current_view = view; }

    virtual void newEvent( const SDL_Event& event);

  protected:

    graphics::ViewPtr m_current_view;
    bool m_quit {false};
};

#endif // GAME_HPP
