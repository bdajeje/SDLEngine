#include "vlayout.hpp"

#include <SDL2/SDL_image.h>

namespace graphics {

VLayout::VLayout(const utils::Configuration& info, const SDL_Rect& parent)
  : Layout{info, parent}
{
  try
  {
    m_item_position = info.get( info::ItemsPos );
  }
  catch(const std::exception& e)
  {
    LOG(ERROR) << "Bad vlayout info file: " << e.what();
  }
}

void VLayout::updateItemsPos(std::shared_ptr<Drawable> object)
{
  // Set x position depending on parent
  object->setPosition( readPosition(m_item_position, m_destination.w, object->destination().w), 0);

  // Update Y position of all items
  int pos_y = 0;
  int shift = m_destination.h / (m_objects.size() + 1);
  for( auto& object : m_objects )
  {
    pos_y += shift;
    object->setPosition( object->posX(), pos_y - (object->height() / 2) );
  }
}

}
