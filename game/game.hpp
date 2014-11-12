#ifndef GAME_HPP
#define GAME_HPP

#include "graphics/view.hpp"

class Game
{
  public:

    void run();

  protected:

    void setCurrentView(graphics::ViewPtr view) { m_current_view = view; }

    virtual void newEvent( const SDL_Event& ) {}

  private:

    graphics::ViewPtr m_current_view;
};

#endif // GAME_HPP
