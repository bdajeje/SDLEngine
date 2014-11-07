#include "main_menu.hpp"

#include "pazaak/textures.hpp"

namespace view {

MainMenu::MainMenu()
{
  // Background
  addObject( std::make_shared<graphics::Drawable>( getTexture(texture::main_menu::Background) ) );
}

}
