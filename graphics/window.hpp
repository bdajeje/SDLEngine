#ifndef PAZAAK_WINDOW_HPP
#define PAZAAK_WINDOW_HPP

#include <SDL2/SDL.h>

#include <string>
#include <memory>

#include "defines.hpp"
#include "game/game.hpp"

namespace graphics {

class Window final
{
  public:

    ~Window();

    static void init(const std::string& title, int width, int height);

    static bool run(std::shared_ptr<Game> game);

    static inline SDL_Window* window() { return s_window; }

    static inline SDL_Surface* screen() { return s_screen; }

  private:

    static SDL_Window* s_window;
    static SDL_Surface* s_screen;
};

}

#endif // PAZAAK_WINDOW_HPP
