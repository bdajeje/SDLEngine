#include "drawable.hpp"

#include "utils/logging/easylogging++.h"
#include "window.hpp"

namespace graphics {

Drawable::Drawable(SDL_Surface* surface)
  : m_surface(surface)
{
}

void Drawable::draw()
{
  if(!m_surface)
  {
    LOG(ERROR) << "Can't draw a null surface!";
    return;
  }

  SDL_BlitSurface( m_surface, NULL, Window::screen(), NULL );
}

}
