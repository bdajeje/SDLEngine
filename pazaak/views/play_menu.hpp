#ifndef PAZAAK_PLAY_MENU_HPP
#define PAZAAK_PLAY_MENU_HPP

#include "pazaak/views/pazaak_menu.hpp"

namespace view {

class PlayMenu final : public PazaakMenu
{
  public:

    PlayMenu(const graphics::Size& size);
};

}

#endif // PAZAAK_PLAY_MENU_HPP
