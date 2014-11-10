#ifndef FONT_MANAGER_HPP
#define FONT_MANAGER_HPP

#include <SDL2/SDL_ttf.h>

#include <map>
#include <memory>
#include <string>

namespace graphics {

class FontManager
{
  public:

    static void init(const std::string& fonts_path);

    ~FontManager();

    static TTF_Font* get(const std::string& path, int size);

    static void clean();

  private:

    FontManager(const std::string& fonts_path);

    TTF_Font* loadFont(const std::string& path, int size, const std::string& font_key);
    static std::string fontKey(const std::string& path, int size);

  private:

    std::string m_fonts_path;
    std::map<std::string, TTF_Font*> m_fonts;

    static std::unique_ptr<FontManager> s_instance;
};

}

#endif // FONT_MANAGER_HPP
