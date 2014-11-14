#ifndef PAZAAK_MAIN_MENU_HPP
#define PAZAAK_MAIN_MENU_HPP

#include "pazaak/views/pazaak_menu.hpp"

namespace view {

class MainMenu final : public PazaakMenu
{
  public:

    MainMenu(const graphics::Size& size);
};

}

#endif // PAZAAK_MAIN_MENU_HPP
