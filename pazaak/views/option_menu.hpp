#ifndef PAZAAK_OPTION_MENU_HPP
#define PAZAAK_OPTION_MENU_HPP

#include "pazaak/views/pazaak_menu.hpp"

namespace view {

class OptionMenu final : public PazaakMenu
{
  public:

    OptionMenu(const graphics::Size& size);

  protected:

    void chooseItem();
};

}

#endif // PAZAAK_OPTION_MENU_HPP
