#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "SDL2/SDL_image.h"

namespace graphics {

class Drawable
{
  public:

    Drawable(SDL_Surface* surface);

    void draw();

  private:

    SDL_Surface* m_surface;
};

}

#endif // DRAWABLE_HPP
