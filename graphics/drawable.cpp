#include "drawable.hpp"

#include "utils/logging/easylogging++.h"
#include "window.hpp"

namespace graphics {

Drawable::Drawable(SDL_Texture* texture)
  : m_texture(texture)
{
}

void Drawable::draw(SDL_Renderer* renderer)
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

  SDL_RenderCopy( renderer, m_texture, NULL, NULL );
}

}
