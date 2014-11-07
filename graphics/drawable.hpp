#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "SDL2/SDL_image.h"

#include "graphics/position.hpp"
#include "graphics/size.hpp"

namespace graphics {

class Drawable
{
  public:

    Drawable(SDL_Texture* texture, const Position& position, const Size& size);

    void draw(SDL_Renderer* renderer);

  private:

    SDL_Rect m_destination;
    SDL_Texture* m_texture;
};

}

#endif // DRAWABLE_HPP
