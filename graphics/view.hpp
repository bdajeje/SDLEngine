#ifndef VIEW_HPP
#define VIEW_HPP

#include <map>
#include <memory>
#include <vector>

#include <SDL2/SDL.h>

#include "drawable.hpp"

namespace graphics {

class View
{
  public:

    View(const Position& position, const Size& size);
    virtual ~View() = default;

    void render(SDL_Renderer* renderer);

  protected:

    void addObject(std::shared_ptr<Drawable>& drawable);
    void addAnimation(std::shared_ptr<Animation>& animation);
    void newFrame();

  private:

    SDL_Rect m_destination;
    std::vector<std::shared_ptr<Drawable>> m_objects;
    std::vector<std::shared_ptr<Drawable>> m_animations;
};

typedef std::shared_ptr<View> ViewPtr;

}

#endif // VIEW_HPP
