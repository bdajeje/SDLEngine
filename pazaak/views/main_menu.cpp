#include "main_menu.hpp"

#include "pazaak/surfaces.hpp"

MainMenu::MainMenu()
{
  // Background
  addObject( std::make_shared<Drawable>( loadSurface(surface::main_menu::Background) ) );
}
