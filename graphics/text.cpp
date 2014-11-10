#include "text.hpp"

#include <boost/algorithm/string.hpp>

#include "engine.hpp"
#include "graphics/manager/font_manager.hpp"

namespace graphics {

Text::Text(const std::string& text, const utils::Configuration& info, const SDL_Rect& parent)
  : Drawable{info, parent}
  , m_text{text}
  , m_font_file{info.get(info::Font)}
{
  try
  {
    // Font properties
    m_font_size = std::stoi(info.get( info::FontSize ));

    // Parse colors
    auto colors_str = info.get( info::FontColor );
    std::vector<std::string> colors;
    boost::algorithm::split(colors, colors_str, boost::is_any_of(","));
    if(colors.size() != 4)
    {
      LOG(ERROR) << "Bad colors syntax in text info file";
      throw std::exception();
    }
    m_color.r = std::stoi(colors[0]);
    m_color.g = std::stoi(colors[1]);
    m_color.b = std::stoi(colors[2]);
    m_color.a = std::stoi(colors[3]);

    // Create text
    loadText();
  }
  catch(const std::exception& e)
  {
    LOG(ERROR) << "Bad font info file: " << e.what();
  }
}

Text::~Text()
{
  // Drawable doesn't destroy its texture because it comes from Texture Manager,
  // In Text class we need to do it manually because we manually loaded this texture.
  clean();
}

void Text::clean()
{
  if(m_texture)
  {
    SDL_DestroyTexture( m_texture );
    m_texture = nullptr;
  }
}

void Text::loadText()
{
  // Destroy previous version of text
  clean();

  SDL_Surface* text_surface = TTF_RenderText_Solid( graphics::FontManager::get(m_font_file, m_font_size), m_text.c_str(), m_color );
  if(!text_surface)
    LOG(ERROR) << "Can't load surface from font: " + m_font_file;

  m_texture = SDL_CreateTextureFromSurface( Engine::renderer(), text_surface );
  SDL_FreeSurface( text_surface );

  // Update size from generated texture
  SDL_QueryTexture(m_texture, NULL, NULL, &m_destination.w, &m_destination.h);
}

void Text::setColor(const SDL_Color& color)
{
  m_color = color;
  loadText();
}

}
