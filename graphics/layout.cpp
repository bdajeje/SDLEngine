#include "layout.hpp"

namespace graphics {

Layout::Layout(const utils::Configuration& info, SDL_Renderer* renderer, const SDL_Rect& parent)
  : Drawable{info, renderer, parent}
  , m_background_destination{0, 0, m_destination.w, m_destination.h}
{}

void Layout::draw(SDL_Renderer* renderer)
{
  SDL_RenderSetViewport(renderer, &m_destination);

  // Draw possible background
  if(m_texture)
    drawTexture( renderer, m_texture, nullptr, m_background_destination );

  // Draw objects
  for( auto& object : m_objects )
    object->draw(renderer);
}

void Layout::addObject(std::shared_ptr<Drawable> object)
{
  m_objects.push_back(object);
  updateItemsPos( object );
}

}
