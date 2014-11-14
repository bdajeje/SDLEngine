#include "option_menu.hpp"

namespace view {

OptionMenu::OptionMenu(const graphics::Size& size)
  : PazaakMenu{ size, "main_menu/menu",
              { "Option Nani?!",
                "Option Nana!" }, "main_menu/text",
              Display::Vertically}
{

}

}
