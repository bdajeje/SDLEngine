#ifndef VIEW_HPP
#define VIEW_HPP

#include <map>
#include <memory>
#include <vector>

#include <SDL2/SDL.h>

#include "graphics/animation.hpp"
#include "graphics/drawable.hpp"

namespace graphics {

class View
{
  public:

    View(const Position& position, const Size& size);
    virtual ~View() = default;

    void render();

    const SDL_Rect& destination() const { return m_destination; }

  protected:

    void addObject(std::shared_ptr<Drawable> drawable);
    void addAnimation(std::shared_ptr<Animation> animation);
    void newFrame();

  private:

    SDL_Rect m_destination;
    std::vector<std::shared_ptr<Drawable>> m_objects;
    std::vector<std::shared_ptr<Animation>> m_animations;
};

typedef std::shared_ptr<View> ViewPtr;

}

#endif // VIEW_HPP
