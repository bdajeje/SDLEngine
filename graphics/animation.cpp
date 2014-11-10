#include "animation.hpp"

#include <boost/algorithm/string.hpp>

#include "defines.hpp"
#include "engine.hpp"
#include "graphics/manager/texture_manager.hpp"

namespace graphics {

Animation::Animation(const utils::Configuration& info, const SDL_Rect& parent)
  : Drawable(info, parent)
{
  try
  {
    setFramerate(std::stoi(info.get( info::Framerate )));

    // Create animation clips
    const int nbr_clips = std::stoi(info.get( info::NbrClips ));
    int texture_width   = 0;
    int texture_height  = 0;
    SDL_QueryTexture(m_texture, NULL, NULL, &texture_width, &texture_height);
    const auto clip_width = texture_width / nbr_clips;

    m_texture_clips.reserve( nbr_clips );
    for(int i = 0; i < nbr_clips; ++i)
      m_texture_clips.push_back( SDL_Rect{clip_width * i, 0, clip_width, texture_height} );
  }
  catch(const std::exception& e)
  {
    LOG(ERROR) << "Bad animation info file: " << e.what();
  }
}

void Animation::setFramerate(uint framerate)
{
  m_framerate = framerate;
  if(m_framerate <= 0)
    m_framerate = 1;
}

void Animation::newFrame()
{
  m_current_frame++;
  if( m_current_frame >= m_framerate * m_texture_clips.size() )
    m_current_frame = 0;

  m_clip = &m_texture_clips[m_current_frame/m_framerate];
}

}
