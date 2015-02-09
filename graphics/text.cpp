#include "text.hpp"

#include <boost/algorithm/string.hpp>

#include "engine.hpp"
#include "graphics/manager/font_manager.hpp"

namespace graphics {

Text::Text(const std::string& text, const utils::Configuration& info, const SDL_Rect& parent)
  : Drawable{info, parent}
{
  try
  {
    // Font properties
    const std::string& font_file = info.get(info::Font);
    auto font_size               = std::stoi(info.get( info::FontSize ));
    SDL_Color normal_color       = parseColor( info.get(info::FontColor) );

    // Create text
    m_normal_texture = createText( text, font_file, font_size, normal_color );
    m_texture = m_normal_texture; // By default text is not selected, so point to m_normal_texture

    // Create selected version of text if needed
    const std::string& selected_color_prop = info.get(info::FontColorSelected);
    if( !selected_color_prop.empty() )
      m_selected_texture = createText( text, font_file, font_size, parseColor( selected_color_prop ) );

    // Update size from generated texture
    SDL_QueryTexture(m_texture, NULL, NULL, &m_destination.w, &m_destination.h);
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
  clean(m_texture);
  clean(m_selected_texture);
}

SDL_Color Text::parseColor(const std::string& color_property)
{
  SDL_Color color;

  static const size_t color_nbr_fields {4};
  std::vector<std::string> colors;
  colors.reserve(color_nbr_fields); // We know there is 4 fields
  boost::algorithm::split(colors, color_property, boost::is_any_of(","));
  if(colors.size() != color_nbr_fields)
  {
    LOG(ERROR) << "Bad colors syntax in text info file";
    throw std::exception();
  }

  color.r = std::stoi(colors[0]);
  color.g = std::stoi(colors[1]);
  color.b = std::stoi(colors[2]);
  color.a = std::stoi(colors[3]);

  return color;
}

void Text::clean( SDL_Texture* texture )
{
  if(texture)
  {
    SDL_DestroyTexture( texture );
    texture = nullptr;
  }
}

SDL_Texture* Text::createText( const std::string& text, const std::string& font_file, int font_size, const SDL_Color& color )
{
  SDL_Surface* text_surface = TTF_RenderText_Solid( Engine::fonts().get(font_file, font_size), text.c_str(), color );
  if(!text_surface)
    LOG(ERROR) << "Can't load surface from font: " + font_file;

  SDL_Texture* texture = SDL_CreateTextureFromSurface( Engine::renderer(), text_surface );
  SDL_FreeSurface( text_surface );

  return texture;
}

void Text::setSelected(bool selected)
{
  m_texture = (selected && m_selected_texture) ? m_selected_texture : m_normal_texture;
}

}
