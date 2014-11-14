#include "pazaak_menu.hpp"
#include "defines.hpp"
#include "graphics/animation.hpp"
#include "pazaak/sounds.hpp"

namespace view {

PazaakMenu::PazaakMenu(const graphics::Size& size, const std::string& menu_info_file,
                       const std::vector<std::string>& texts, const std::string& text_info_file, Display display)
  : Menu{ size, menu_info_file, texts, text_info_file, display, "main_menu/background"}
{
  // Logo
  utils::Configuration logo_info {IMAGE_INFO_PATH, {"main_menu/logo"}};
  m_logo = std::make_shared<graphics::Animation>( logo_info, destination() );
  addAnimation( m_logo );

  // We need to re-set the focus because of the logo
  setFocus( selectedItem() );

  // Set change selection sound (after setting the focus so we do not play a sound when menu is created)
  setChangeItemSound(sound::menu::CHANGE_ITEM);
  setChooseItemSound(sound::menu::SELECT_ITEM);
}

void PazaakMenu::setFocus(const std::shared_ptr<graphics::Text>& newly_selected_item)
{
  Menu::setFocus(newly_selected_item);

  // Place logo on current selected menu item
  static const int x_margin = 20;
  m_logo->setPosition( newly_selected_item->posX() - m_logo->width()- x_margin, newly_selected_item->posY() );
}

}
