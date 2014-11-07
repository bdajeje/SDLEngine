#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>

#include "graphics/drawable.hpp"

namespace graphics {

class Animation : public Drawable
{
  public:

    /* Constructor
     * \param framerate the animation is uddate every framerate
     */
    Animation(uint framerate, std::vector<SDL_Texture*> textures, const Position& position, const Size& size);

    void draw(SDL_Renderer* renderer);
    void newFrame();

  private:

    uint m_framerate;
    uint m_current_frame {0};
    std::vector<SDL_Texture*> m_textures;
};

}

#endif // ANIMATION_HPP
