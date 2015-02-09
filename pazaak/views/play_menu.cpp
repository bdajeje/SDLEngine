#include "play_menu.hpp"

#include "defines.hpp"

namespace view {

PlayMenu::PlayMenu(const graphics::Size& size)
  : PazaakMenu{ size, "main_menu/menu", Display::Vertically}
{
  utils::Configuration text_info {IMAGE_INFO_PATH, {"main_menu/text"}};
  addMenuItem( std::make_shared<graphics::Text>("TODO", text_info) );
  setFocus(m_items.front(), false);
}

}
