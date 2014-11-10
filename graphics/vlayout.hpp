#ifndef VLAYOUT_HPP
#define VLAYOUT_HPP

#include "graphics/layout.hpp"

namespace graphics {

/*
 * Note: in Layouts, m_texture coming from Drawable represents a possible background for the layout
 */
class VLayout final : public Layout
{
  public:

    VLayout(const utils::Configuration& info, SDL_Renderer* renderer, const SDL_Rect& parent);

  protected:

    void updateItemsPos(std::shared_ptr<Drawable> object);
};

}

#endif // VLAYOUT_HPP
