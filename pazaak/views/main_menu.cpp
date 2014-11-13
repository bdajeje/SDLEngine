#include "main_menu.hpp"

#include "defines.hpp"
#include "graphics/animation.hpp"
#include "utils/translations.hpp"

#include "pazaak/sounds.hpp"
#include "pazaak/translations.hpp"

namespace view {

MainMenu::MainMenu(const graphics::Size& size)
  : Menu{ size, "main_menu/menu",
          { utils::Translations::translate(translations::MainMenu::Play),
            utils::Translations::translate(translations::MainMenu::Settings),
            utils::Translations::translate(translations::MainMenu::Quit) }, "main_menu/text",
          Display::Vertically, "main_menu/background"}
{
  // Logo
  utils::Configuration logo_info {IMAGE_INFO_PATH, {"main_menu/logo"}};
  m_logo = std::make_shared<graphics::Animation>( logo_info, destination() );
  addAnimation( m_logo );

  // We need to re-set the focus because of the logo
  setFocus( selectedItem() );

  // Set change selection sound (after setting the focus so we do not play a sound when menu is created)
  setChangeSelectionSound(sound::menu::CHANGE_SELECTION);
}

void MainMenu::setFocus(const std::shared_ptr<graphics::Text>& newly_selected_item)
{
  Menu::setFocus(newly_selected_item);

  // Place logo on current selected menu item
  static const int x_margin = 20;
  m_logo->setPosition( newly_selected_item->posX() - m_logo->width()- x_margin, newly_selected_item->posY() );
}

}
