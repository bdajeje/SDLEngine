#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <string>

#include "SDL2/SDL_image.h"

#include "graphics/position.hpp"
#include "graphics/size.hpp"
#include "utils/configuration/configuration.hpp"

namespace graphics {

namespace info {
  static const std::string Width {"width"};
  static const std::string Height {"height"};
  static const std::string PosX {"pos_x"};
  static const std::string PosY {"pos_y"};
  static const std::string Texture {"texture"};
}

class Drawable
{
  public:

    Drawable(const utils::Configuration& info, SDL_Renderer* renderer, const SDL_Rect& parent);
    Drawable(SDL_Texture* texture, const Position& position, const Size& size);
    virtual ~Drawable() = default;

    virtual void draw(SDL_Renderer* renderer);

  protected:

    /* There are two different ways to read a size
     * 1/ number     -> take it as it is
     * 2/ percentage -> result is percentage of parent size
     * \param info      is string to parse, either a number (like '124') or a percentage (like '55%')
     * \param reference useful only when info is a percentage so we take percentage of the reference
     * \note can throw
     */
    int readNumberOrPercentage( const std::string& info, int reference );

  protected:

    SDL_Texture* m_texture;
    SDL_Rect m_destination;

    // Uses to draw only a part of the texture
    // Note: Yet not used by drawable
    // Note: Used for animations
    SDL_Rect* m_clip {nullptr};
};

}

#endif // DRAWABLE_HPP
