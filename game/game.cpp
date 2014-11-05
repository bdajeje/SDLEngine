#include "game.hpp"

#include "utils/logging/easylogging++.h"

Game::Game()
{
}

void Game::draw()
{
  if(!m_current_view)
  {
    LOG(ERROR) << "Game with no valid view!";
    return;
  }

  m_current_view->draw();
}
