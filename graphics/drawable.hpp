#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "SDL2/SDL_image.h"

namespace graphics {

class Drawable
{
  public:

    Drawable(SDL_Texture* texture);

    void draw(SDL_Renderer* renderer);

  private:

    SDL_Texture* m_texture;
};

}

#endif // DRAWABLE_HPP
