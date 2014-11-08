#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>

#include "graphics/drawable.hpp"

namespace graphics {

namespace info {
  static const std::string Framerate {"framerate"};
  static const std::string NbrClips {"nbr_clips"};
}

class Animation : public Drawable
{
  public:

    Animation(const utils::Configuration& info, SDL_Renderer* renderer, const SDL_Rect& parent);

    void newFrame();

  private:

    void setFramerate(uint framerate);

  private:

    uint m_framerate;
    uint m_current_frame {0};
    std::vector<SDL_Rect> m_texture_clips;
};

}

#endif // ANIMATION_HPP
