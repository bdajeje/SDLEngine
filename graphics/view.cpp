#include "view.hpp"

#include "utils/logging/easylogging++.h"
#include "window.hpp"

namespace graphics {

View::View(const Position& position, const Size& size)
  : m_destination{ position.x, position.y, size.w, size.h }
{}

void View::render(SDL_Renderer* renderer)
{
  SDL_RenderSetViewport(renderer, &m_destination);

  // Draw all elements of the view
  for(auto object : m_objects)
    object->draw(renderer);
}

void View::addObject(std::shared_ptr<Drawable>& drawable)
{
  if(!drawable)
  {
    LOG(ERROR) << "Trying to add a null object to the view";
    return;
  }

  m_objects.push_back(drawable);
}

}
