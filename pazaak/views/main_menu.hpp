#ifndef PAZAAK_MAIN_MENU_HPP
#define PAZAAK_MAIN_MENU_HPP

#include "graphics/size.hpp"
#include "graphics/view.hpp"

namespace view {

class MainMenu final : public graphics::View
{
  public:

    MainMenu(SDL_Renderer* renderer, const graphics::Size& size);
};

}

#endif // PAZAAK_MAIN_MENU_HPP
