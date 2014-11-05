#include "main_menu.hpp"

#include "pazaak/surfaces.hpp"

namespace view {

MainMenu::MainMenu()
{
  // Background
  addObject( std::make_shared<graphics::Drawable>( loadSurface(surface::main_menu::Background) ) );
}

}
