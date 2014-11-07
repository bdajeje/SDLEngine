#include "animation.hpp"

namespace graphics {

Animation::Animation(uint framerate, const std::vector<SDL_Texture*>& textures, const Position& position, const Size& size)
  : Drawable(position, size)
  , m_current_frame(framerate)
  , m_textures(textures)
{
}

void Animation::draw(SDL_Renderer* renderer)
{
  if(m_textures.empty())
  {
    LOG(ERROR) << "Can't draw an animation with no textures!";
    return;
  }
  else if(!renderer)
  {
    LOG(ERROR) << "How do you want me do draw with a NULL renderer?";
    return;
  }

  SDL_RenderCopy( renderer, m_textures[m_current_frame/m_framerate], NULL, &m_destination );
}

void Animation::newFrame()
{
  m_current_frame++;
  if( m_current_frame >= m_framerate * m_textures.size() )
    m_current_frame = 0;
}

}
