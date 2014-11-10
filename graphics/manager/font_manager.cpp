#include "font_manager.hpp"

#include "utils/logging/easylogging++.h"

namespace graphics {

std::unique_ptr<FontManager> FontManager::s_instance;

void FontManager::init(const std::string &fonts_path)
{
  if(s_instance)
    return;

  s_instance.reset( new FontManager(fonts_path) );
}

FontManager::FontManager(const std::string& fonts_path)
  : m_fonts_path(fonts_path)
{}

FontManager::~FontManager()
{
  clean();
}

void FontManager::clean()
{
  // Delete all fonts
  for(auto font : s_instance->m_fonts)
    TTF_CloseFont(font.second);
  s_instance->m_fonts.clear();
}

std::string FontManager::fontKey(const std::string& path, int size)
{
  return path + std::to_string(size);
}

TTF_Font* FontManager::get(const std::string& path, int size)
{
  if(!s_instance)
  {
    LOG(ERROR) << "Trying to use a NULL font manager!";
    return nullptr;
  }

  // Find already loaded image
  const std::string font_key = fontKey(path, size);
  auto found = s_instance->m_fonts.find( font_key );
  if( found != s_instance->m_fonts.end() )
    return found->second;

  // Image not yet loaded
  return s_instance->loadFont(path, size, font_key);
}

TTF_Font* FontManager::loadFont(const std::string& path, int size, const std::string& font_key)
{
  // Load image at specified path
  const std::string full_path = m_fonts_path + path;
  TTF_Font* font = TTF_OpenFont( full_path.c_str(), size );
  if( !font )
  {
    LOG(ERROR) << "Unable to load font " << full_path.c_str() << "! SDL_ttf Error: " << TTF_GetError();
    return nullptr;
  }

  // Save font in cache
  m_fonts[font_key] = font;

  return font;
}

}
