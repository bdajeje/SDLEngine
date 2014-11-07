#include "view.hpp"

#include "defines.hpp"
#include "utils/logging/easylogging++.h"
#include "window.hpp"

namespace graphics {

View::~View()
{
  // Delete all textures
  for(auto texture : m_textures)
    SDL_DestroyTexture(texture.second);
}

void View::draw(SDL_Renderer* renderer)
{
  // Draw all elements of the view
  for(auto object : m_objects)
    object->draw(renderer);
}

void View::addObject(std::shared_ptr<Drawable> drawable)
{
  if(!drawable)
  {
    LOG(ERROR) << "Trying to add a null object to the view";
    return;
  }

  m_objects.push_back(drawable);
}

SDL_Texture* View::getTexture(const std::string& path)
{
  // Find already loaded image
  auto found = m_textures.find(path);
  if( found != m_textures.end() )
    return found->second;

  // Image not yet loaded
  return loadTexture(path);
}

SDL_Texture* View::loadTexture(const std::string& path)
{
  // Load image at specified path
  const std::string full_path = TEXTURE_PATH + path;
  SDL_Surface* surface = IMG_Load( full_path.c_str() );
  if( !surface )
  {
    LOG(ERROR) << "Unable to load image " << full_path.c_str() << "! SDL_image Error: " << IMG_GetError();
    return nullptr;
  }

  // Convert surface to screen format
  SDL_Texture* texture = SDL_CreateTextureFromSurface( m_renderer, surface );

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
