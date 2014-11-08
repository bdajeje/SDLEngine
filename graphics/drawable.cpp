#include "drawable.hpp"

#include "graphics/manager/texture_manager.hpp"
#include "graphics/window.hpp"
#include "utils/logging/easylogging++.h"

namespace graphics {

Drawable::Drawable(SDL_Texture* texture, const Position& position, const Size& size)
  : m_texture(texture)
  , m_destination{ position.x, position.y, size.w, size.h }
{}

Drawable::Drawable(const utils::Configuration& info, SDL_Renderer* renderer, const SDL_Rect& parent)
{
  try
  {
    // Size
    m_destination.w = readNumberOrPercentage(info.get( info::Width ), parent.w);
    m_destination.h = readNumberOrPercentage(info.get( info::Height ), parent.h);

    // Position
    m_destination.x = readNumberOrPercentage(info.get( info::PosX ), parent.x);
    m_destination.y = readNumberOrPercentage(info.get( info::PosY ), parent.y);

    // Texture
    const std::string& texture_path = info.get( info::Texture );
    m_texture = graphics::TextureManager::get(texture_path, renderer);
  }
  catch(const std::exception& e)
  {
    LOG(ERROR) << "Bad image info file: " << e.what();
  }
}

void Drawable::draw(SDL_Renderer* renderer)
{
  if(!m_texture)
  {
    LOG(ERROR) << "Can't draw with a NULL texture!";
    return;
  }
  else if(!renderer)
  {
    LOG(ERROR) << "How do you want me do draw with a NULL renderer?";
    return;
  }

  SDL_RenderCopy( renderer, m_texture, m_clip, &m_destination );
}

int Drawable::readNumberOrPercentage( const std::string& info, int reference )
{
  if( info.back() == '%' )
  {
    auto percentage = stof( info.substr(0, info.length() - 1) );
    return percentage * reference / 100;
  }
  else
    return std::stoi(info);
}

}
