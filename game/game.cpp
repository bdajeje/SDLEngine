#include "game.hpp"

#include "utils/logging/easylogging++.h"

void Game::draw(SDL_Renderer* renderer)
{
  if(!m_current_view)
  {
    LOG(ERROR) << "Game with no valid view!";
    return;
  }

  m_current_view->draw(renderer);
}
