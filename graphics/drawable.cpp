#include "drawable.hpp"

#include "engine.hpp"
#include "graphics/manager/texture_manager.hpp"

namespace graphics {

Drawable::Drawable(SDL_Texture* texture, const Position& position, const Size& size)
  : m_texture(texture)
  , m_destination{ position.x, position.y, size.w, size.h }
{}

Drawable::Drawable(const utils::Configuration& info, const SDL_Rect& parent)
{
  try
  {
    // Size
    m_destination.w = readNumberOrPercentage(info.get( info::Width ), parent.w);
    m_destination.h = readNumberOrPercentage(info.get( info::Height ), parent.h);

    // Position
    // \warning this has to be called after finding sizes, because we need them here
    m_destination.x = readPosition(info.get( info::PosX ), parent.w, m_destination.w);
    m_destination.y = readPosition(info.get( info::PosY ), parent.h, m_destination.h);

    // Texture
    const std::string& texture_path = info.get( info::Texture );
    if(!texture_path.empty())
      m_texture = graphics::TextureManager::get(texture_path);
  }
  catch(const std::exception& e)
  {
    LOG(ERROR) << "Bad image info file: " << e.what();
  }
}

void Drawable::draw()
{
  if(m_texture)
    drawTexture( m_texture, m_clip, m_destination );
}

void Drawable::drawTexture(SDL_Texture* texture, SDL_Rect* clip, const SDL_Rect& destination)
{
  SDL_RenderCopy( Engine::renderer(), texture, clip, &destination );
}

int Drawable::readNumberOrPercentage( const std::string& info, int reference )
{
  if(info.empty())
    return 0;
  else if( info.back() == '%' )
  {
    auto percentage = stof( info.substr(0, info.length() - 1) );
    return percentage * reference / 100;
  }
  else
    return std::stoi(info);
}

int Drawable::readPosition(const std::string& info, int reference, int size)
{
  if(info.empty())
    return 0;
  else if(info.front() >= '0' && info.front() <= '9')
    return readNumberOrPercentage(info, reference);
  else if( info == position::Centered )
    return (reference - size) / 2;

  return 0;
}

void Drawable::setPosition(const Position& position)
{
  setPosition(position.x, position.y);
}

void Drawable::setPosition(int x, int y)
{
  m_destination.x = x;
  m_destination.y = y;
}

}
