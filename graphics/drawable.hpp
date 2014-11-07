#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "SDL2/SDL_image.h"

#include "graphics/position.hpp"
#include "graphics/size.hpp"

namespace graphics {

class Drawable
{
  public:

    Drawable(const Position& position, const Size& size);

    virtual void draw(SDL_Renderer* renderer) = 0;

  private:

    SDL_Rect m_destination;
};

}

#endif // DRAWABLE_HPP
