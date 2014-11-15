#include "option_menu.hpp"
#include "pazaak/translations.hpp"

#include "utils/translations.hpp"

namespace view {

OptionMenu::OptionMenu(const graphics::Size& size)
  : PazaakMenu{ size, "main_menu/menu",
              { utils::Translations::translate(translations::OptionMenu::Sound),
                utils::Translations::translate(translations::OptionMenu::Music),
                utils::Translations::translate(translations::Menu::Back)}, "main_menu/text",
              Display::Vertically}
{

}

void OptionMenu::chooseItem()
{
  PazaakMenu::chooseItem();

  if( m_selected_item_pos == 2 )
    previousViewEvent();
}

}
