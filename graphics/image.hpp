#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "SDL2/SDL_image.h"

#include "graphics/drawable.hpp"

namespace graphics {

class Image : public Drawable
{
  public:

    Image(SDL_Texture* texture, const Position& position, const Size& size);

    void draw(SDL_Renderer* renderer);

  private:

    SDL_Texture* m_texture;
};

}

#endif // IMAGE_HPP
