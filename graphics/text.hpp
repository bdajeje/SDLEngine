#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL_ttf.h>

#include "graphics/drawable.hpp"

namespace graphics {

namespace info {
  static const std::string Font {"font"};
  static const std::string FontSize {"font_size"};
  static const std::string FontColor {"font_color"};
}

class Text final : public Drawable
{
  public:

    Text(const std::string& text, const utils::Configuration& info, const SDL_Rect& parent = {0,0,0,0});
    ~Text();

    const SDL_Color& color() const { return m_color; }

    void setColor(const SDL_Color& color);

  private:

    void clean();
    void loadText();

  private:

    SDL_Color m_color;
    std::string m_text;
    std::string m_font_file;
    int m_font_size;
};

}

#endif // TEXT_HPP
