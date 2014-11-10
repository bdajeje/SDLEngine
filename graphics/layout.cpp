#include "layout.hpp"

#include "engine.hpp"

namespace graphics {

Layout::Layout(const utils::Configuration& info, const SDL_Rect& parent)
  : Drawable{info, parent}
  , m_background_destination{0, 0, m_destination.w, m_destination.h}
{}

void Layout::draw()
{
  SDL_RenderSetViewport(Engine::renderer(), &m_destination);

  // Draw possible background
  if(m_texture)
    drawTexture( m_texture, nullptr, m_background_destination );

  // Draw objects
  for( auto& object : m_objects )
    object->draw();
}

void Layout::addObject(std::shared_ptr<Drawable> object)
{
  m_objects.push_back(object);
  updateItemsPos( object );
}

}
