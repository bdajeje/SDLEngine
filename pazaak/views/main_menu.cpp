#include "main_menu.hpp"

#include "graphics/animation.hpp"
#include "graphics/manager/texture_manager.hpp"
#include "pazaak/textures.hpp"

namespace view {

MainMenu::MainMenu(SDL_Renderer* renderer, const graphics::Size& size)
  : View{ graphics::Position{0,0}, size }
{
  // Background
  auto background = std::make_shared<graphics::Drawable>( graphics::TextureManager::get(texture::main_menu::Background, renderer), graphics::Position{0,0}, size );
  addObject( background );

  // Logo
  // \todo create helper method to load image and/or animation from file with information like position - size - texture(s) so we do not have to recompile to update the design
  AnimationInfo animation = loadAnimation("main_menu/logo", renderer);
  auto logo = std::make_shared<graphics::Animation>( animation.textures, animation.position, animation.size );
  addAnimation( logo );
}

}
