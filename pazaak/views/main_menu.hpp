#ifndef PAZAAK_MAIN_MENU_HPP
#define PAZAAK_MAIN_MENU_HPP

#include "graphics/menu.hpp"

namespace view {

class MainMenu final : public graphics::Menu
{
  public:

    MainMenu(const graphics::Size& size);

  private:

    void setFocus(const std::shared_ptr<graphics::Text>& newly_selected_item);

  private:

    std::shared_ptr<graphics::Animation> m_logo;
};

}

#endif // PAZAAK_MAIN_MENU_HPP
