#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL_ttf.h>

#include "graphics/drawable.hpp"

namespace graphics {

namespace info {
  static const std::string Font {"font"};
  static const std::string FontSize {"font_size"};
  static const std::string FontColor {"font_color"};
  static const std::string FontColorSelected {"font_color_selected"};
}

class Text final : public Drawable
{
  public:

    Text(const std::string& text, const utils::Configuration& info, const SDL_Rect& parent = {0,0,0,0});
    ~Text();

    void setSelected(bool selected);

  private:

    static void clean( SDL_Texture* texture );
    static SDL_Texture* createText( const std::string& text, const std::string& font_file, int font_size, const SDL_Color& color );
    static SDL_Color parseColor(const std::string& color_property);

  private:

    SDL_Texture* m_normal_texture;             // Texture to display when not selected
    SDL_Texture* m_selected_texture {nullptr}; // Texture to display when selected
};

}

#endif // TEXT_HPP
