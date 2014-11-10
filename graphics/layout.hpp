#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include <memory>
#include <vector>

#include "graphics/drawable.hpp"

namespace graphics {

namespace info {
  static const std::string ItemsPos {"items_pos"};
}

class Layout : public Drawable
{
  public:

    Layout(const utils::Configuration& info, SDL_Renderer* renderer, const SDL_Rect& parent);
    virtual ~Layout() = default;

    void draw(SDL_Renderer* renderer);
    void addObject(std::shared_ptr<Drawable> object);

    std::shared_ptr<Drawable> getObject( size_t offset ) const { return m_objects.at(offset); }
    const std::vector<std::shared_ptr<Drawable>>& objects() const { return m_objects; }

  protected:

    virtual void updateItemsPos(std::shared_ptr<Drawable> object) = 0;

  protected:

    SDL_Rect m_background_destination;
    std::vector<std::shared_ptr<Drawable>> m_objects;
    std::string m_item_position;
};

}

#endif // LAYOUT_HPP
