#ifndef PAZAAK_WINDOW_HPP
#define PAZAAK_WINDOW_HPP

#include <SDL2/SDL.h>

#include <memory>
#include <string>

#include "graphics/view.hpp"

namespace graphics {

class Window final
{
  public:

    Window(const std::string& title, int width, int height);
    ~Window();

    void clear();
    void render(graphics::ViewPtr view);

    SDL_Renderer* renderer() const { return m_renderer; }

  private:

    SDL_Window*   m_window;
    SDL_Renderer* m_renderer;
};

}

#endif // PAZAAK_WINDOW_HPP
