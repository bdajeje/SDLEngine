#include "play_menu.hpp"

namespace view {

PlayMenu::PlayMenu(const graphics::Size& size)
  : PazaakMenu{ size, "main_menu/menu",
              { "Nani?!",
                "Nana!" }, "main_menu/text",
              Display::Vertically}
{
}

}
