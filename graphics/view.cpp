#include "view.hpp"

#include <SDL2/SDL_image.h>

#include "defines.hpp"
#include "utils/logging/easylogging++.h"
#include "window.hpp"

namespace graphics {

View::View()
{
}

View::~View()
{
  // Delete all surfaces in the view
  for(auto surface : m_surfaces)
    SDL_FreeSurface(surface.second);
}

void View::draw()
{
  // Draw all elements of the view
  for(auto object : m_objects)
    object->draw();
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

SDL_Surface* View::loadSurface( const std::string& path )
{
  // Find already loaded image
  auto found = m_surfaces.find(path);
  if( found != m_surfaces.end() )
    return found->second;

  // Image not yet loaded
  // Load image at specified path
  SDL_Surface* surface = IMG_Load( (Resources_folder + Images_folder + path).c_str() );
  if( !surface )
  {
    LOG(ERROR) << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << " \n";
    return nullptr;
  }

  // Convert surface to screen format
  SDL_Surface* optimized_surface = SDL_ConvertSurface( surface, Window::screen()->format, NULL );
  if( !optimized_surface )
  {
    LOG(ERROR) << "Unable to optimize image " << path.c_str() << "! SDL Error: " << SDL_GetError() << "\n";
    return nullptr;
  }

  // Get rid of old loaded surface
  SDL_FreeSurface( surface );

  // Save surface for future use
  m_surfaces[path] = optimized_surface;

  return optimized_surface;
}

}
