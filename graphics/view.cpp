#include "view.hpp"

#include "engine.hpp"
#include "utils/logging/easylogging++.h"

namespace graphics {

View::View(const Position& position, const Size& size)
  : m_destination{ position.x, position.y, size.w, size.h }
{}

void View::render()
{
  newFrame();

  SDL_RenderSetViewport(Engine::renderer(), &m_destination);

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

void View::addAnimation(std::shared_ptr<Animation> animation)
{
  if(!animation)
  {
    LOG(ERROR) << "Trying to add a null animation to the view";
    return;
  }

  m_animations.push_back(animation);

  // Also add the animation to the drawable list to be drawn
  addObject(animation);
}

void View::newFrame()
{
  for( auto& animation : m_animations )
    animation->newFrame();
}

}
