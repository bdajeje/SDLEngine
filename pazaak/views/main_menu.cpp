#include "main_menu.hpp"

#include "defines.hpp"
#include "graphics/animation.hpp"
#include "graphics/manager/texture_manager.hpp"
#include "pazaak/textures.hpp"

namespace view {

MainMenu::MainMenu(SDL_Renderer* renderer, const graphics::Size& size)
  : View{ graphics::Position{0,0}, size }
{
  // Background
  utils::Configuration background_info {IMAGE_INFO_PATH, {"main_menu/background"}};
  addObject( std::make_shared<graphics::Drawable>(background_info, renderer, destination() ) );

  // Logo
  utils::Configuration logo_info {IMAGE_INFO_PATH, {"main_menu/logo"}};
  addAnimation( std::make_shared<graphics::Animation>( logo_info, renderer, destination() ) );
}

}
