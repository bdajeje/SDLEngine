#include "main_menu.hpp"

#include "graphics/manager/texture_manager.hpp"
#include "pazaak/textures.hpp"

namespace view {

MainMenu::MainMenu(SDL_Renderer* renderer, const graphics::Size& size)
  : View{ graphics::Position{0,0}, size }
{
  // Background
  auto background = std::make_shared<graphics::Drawable>( graphics::TextureManager::get(texture::main_menu::Background, renderer), graphics::Position{0,0}, size );
  addObject( background );
}

}
