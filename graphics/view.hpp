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
    virtual void newEvent( const SDL_Event& event );

    const SDL_Rect& destination() const { return m_destination; }

    void setPreviousView( std::shared_ptr<View> previous_view ) { m_previous_view = previous_view; }
    std::shared_ptr<View> previousView() const { return m_previous_view; }

  protected:

    void addObject(std::shared_ptr<Drawable> drawable);
    void addAnimation(std::shared_ptr<Animation> animation);
    void newFrame();
    void previousViewEvent();

  private:

    SDL_Rect m_destination;
    std::vector<std::shared_ptr<Drawable>> m_objects;
    std::vector<std::shared_ptr<Animation>> m_animations;
    std::shared_ptr<View> m_previous_view;
};

typedef std::shared_ptr<View> ViewPtr;

}

#endif // VIEW_HPP
