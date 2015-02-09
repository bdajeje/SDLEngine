#ifndef PAZAAK_OPTION_MENU_HPP
#define PAZAAK_OPTION_MENU_HPP

#include "pazaak/views/pazaak_menu.hpp"

namespace view {

class OptionMenuSetting final : public graphics::Menu
{
  public:

    OptionMenuSetting(const graphics::Size& size, std::shared_ptr<graphics::Text> title, std::shared_ptr<graphics::Drawable> content);
};

class OptionMenu final : public PazaakMenu
{
  public:

    OptionMenu(const graphics::Size& size);
};

}

#endif // PAZAAK_OPTION_MENU_HPP
