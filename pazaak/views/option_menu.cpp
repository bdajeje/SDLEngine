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
  DrawableEventBinder::bind( m_items[2], std::bind(&OptionMenu::previousViewEvent, this) );
}

}
