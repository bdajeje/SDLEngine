#include "drawable.hpp"

#include "utils/logging/easylogging++.h"
#include "window.hpp"

namespace graphics {

Drawable::Drawable(SDL_Texture* texture, const Position& position, const Size& size)
  : m_destination{ position.x, position.y, size.w, size.h }
{}

}
