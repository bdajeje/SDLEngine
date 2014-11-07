#ifndef PAZAAK_WINDOW_HPP
#define PAZAAK_WINDOW_HPP

#include <SDL2/SDL.h>

#include <map>
#include <memory>
#include <string>

#include "defines.hpp"
#include "game/game.hpp"

namespace graphics {

class Window final
{
  public:

    Window(const std::string& title, int width, int height);
    ~Window();

    bool run(std::shared_ptr<Game> game);

  private:

    SDL_Window*   m_window;
    SDL_Renderer* m_renderer;
};

}

#endif // PAZAAK_WINDOW_HPP
