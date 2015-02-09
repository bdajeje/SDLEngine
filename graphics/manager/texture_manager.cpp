#include "texture_manager.hpp"

#include <SDL2/SDL_image.h>

#include "engine.hpp"
#include "utils/logging/easylogging++.h"

namespace graphics {

TextureManager::TextureManager(const std::string& textures_path)
  : m_textures_path(textures_path)
{}

TextureManager::~TextureManager()
{
  // Delete all textures
  for(auto texture : m_textures)
    SDL_DestroyTexture(texture.second);

  m_textures.clear();
}

SDL_Texture* TextureManager::get(const std::string& path)
{
  // Find already loaded image
  auto found = m_textures.find(path);
  if( found != m_textures.end() )
    return found->second;

  // Image not yet loaded
  return loadTexture(path);
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
