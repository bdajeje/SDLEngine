#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <string>

#include <SDL2/SDL_image.h>

#include "graphics/position.hpp"
#include "graphics/size.hpp"
#include "utils/configuration/configuration.hpp"
#include "utils/logging/easylogging++.h"

namespace graphics {

namespace info {
  static const std::string Width {"width"};
  static const std::string Height {"height"};
  static const std::string PosX {"pos_x"};
  static const std::string PosY {"pos_y"};
  static const std::string Texture {"texture"};
}

namespace position {
  static const std::string Centered {"centered"};
}

class Drawable
{
  public:

    Drawable(const utils::Configuration& info, SDL_Renderer* renderer, const SDL_Rect& parent);
    Drawable(SDL_Texture* texture, const Position& position, const Size& size);
    virtual ~Drawable() = default;

    virtual void draw(SDL_Renderer* renderer);

    void setPosition(const Position& position);
    void setPosition(int x, int y);

    const SDL_Rect& destination() const { return m_destination; }
    int width() const { return m_destination.w; }
    int height() const { return m_destination.h; }
    int posX() const { return m_destination.x; }
    int posY() const { return m_destination.y; }

  protected:

    /* There are two different ways to read a size
     * 1/ number     -> take it as it is
     * 2/ percentage -> result is percentage of parent size
     * \param info      is string to parse, either a number (like '124') or a percentage (like '55%')
     * \param reference useful only when info is a percentage so we take percentage of the reference
     * \note can throw
     */
    int readNumberOrPercentage( const std::string& info, int reference );

    /* Positions could be
     * 1/ like for readNumberOrPercentage
     * 2/ string -> 'centered' to horizontally or vertically centered the object from it parent
     * \warning \todo if reference < size leads to unexpected behavior
     */
    int readPosition(const std::string& info, int reference, int size);

    void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* clip, const SDL_Rect& destination);

  protected:

    SDL_Texture* m_texture {nullptr}; // We do not own this pointer
    SDL_Rect m_destination;

    // Uses to draw only a part of the texture
    // Note: Yet not used by drawable
    // Note: Used for animations
    SDL_Rect* m_clip {nullptr};
};

}

#endif // DRAWABLE_HPP
