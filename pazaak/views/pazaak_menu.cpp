#include "pazaak_menu.hpp"

#include "engine.hpp"
#include "defines.hpp"
#include "graphics/animation.hpp"

#include "pazaak/sounds.hpp"

namespace view {

PazaakMenu::PazaakMenu(const graphics::Size& size, const std::string& menu_info_file, Display display)
  : Menu{ size, menu_info_file, display, "main_menu/background"}
{
  // Logo
  utils::Configuration logo_info {IMAGE_INFO_PATH, {"main_menu/logo"}};
  m_logo = std::make_shared<graphics::Animation>( logo_info, destination() );
  addAnimation( m_logo );

  // Set change selection sound (after setting the focus so we do not play a sound when menu is created)
  setChangeItemSound(sound::menu::CHANGE_ITEM);
  setChooseItemSound(sound::menu::SELECT_ITEM);

  KeyboardEventBinder::bind( SDLK_ESCAPE, std::bind(&PazaakMenu::previousViewEvent, this) );
}

void PazaakMenu::setFocus(const std::shared_ptr<graphics::Drawable> newly_selected_item, bool play_sound)
{
  Menu::setFocus(newly_selected_item, play_sound);

  // Place logo on current selected menu item
  static const int x_margin = 20;
  m_logo->setPosition( newly_selected_item->posX() - m_logo->width()- x_margin, newly_selected_item->posY() );
}

void PazaakMenu::previousViewEvent()
{
  SDL_Event event {Engine::events().PreviousView};
  SDL_PushEvent(&event);
}

}
