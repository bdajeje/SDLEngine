#include "image.hpp"

namespace graphics {

Image::Image(SDL_Texture* texture, const Position& position, const Size& size)
  : Drawable(position, size)
  , m_texture{texture}
{}

void Image::draw(SDL_Renderer* renderer)
{
  if(!m_texture)
  {
    LOG(ERROR) << "Can't draw a null surface!";
    return;
  }
  else if(!renderer)
  {
    LOG(ERROR) << "How do you want me do draw with a NULL renderer?";
    return;
  }

  SDL_RenderCopy( renderer, m_texture, NULL, &m_destination );
}

}
