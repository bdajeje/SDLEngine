#include "texture_manager.hpp"

#include <SDL2/SDL_image.h>

#include "engine.hpp"
#include "utils/logging/easylogging++.h"

namespace graphics {

std::unique_ptr<TextureManager> TextureManager::s_instance;

void TextureManager::init(const std::string &textures_path)
{
  if(s_instance)
    return;

  s_instance.reset( new TextureManager(textures_path) );
}

TextureManager::TextureManager(const std::string& textures_path)
  : m_textures_path(textures_path)
{}

TextureManager::~TextureManager()
{
  clean();
}

void TextureManager::clean()
{
  // Delete all textures
  for(auto texture : s_instance->m_textures)
    SDL_DestroyTexture(texture.second);
  s_instance->m_textures.clear();
}

SDL_Texture* TextureManager::get(const std::string& path)
{
  if(!s_instance)
  {
    LOG(ERROR) << "Trying to use a NULL texture manager!";
    return nullptr;
  }

  // Find already loaded image
  auto found = s_instance->m_textures.find(path);
  if( found != s_instance->m_textures.end() )
    return found->second;

  // Image not yet loaded
  return s_instance->loadTexture(path);
}

SDL_Texture* TextureManager::loadTexture(const std::string& path)
{
  // Load image at specified path
  const std::string full_path = m_textures_path + path;
  SDL_Surface* surface = IMG_Load( full_path.c_str() );
  if( !surface )
  {
    LOG(ERROR) << "Unable to load image " << full_path.c_str() << "! SDL_image Error: " << IMG_GetError();
    return nullptr;
  }

  // Convert surface to screen format
  SDL_Texture* texture = SDL_CreateTextureFromSurface( Engine::renderer(), surface );

  // Get rid of old loaded surface
  SDL_FreeSurface( surface );

  if( !texture )
  {
    LOG(ERROR) << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError();
    return nullptr;
  }

  // Save texture in cache
  m_textures[path] = texture;

  return texture;
}

}
