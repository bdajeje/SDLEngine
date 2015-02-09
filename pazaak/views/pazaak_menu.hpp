#ifndef PAZAAK_MENU_HPP
#define PAZAAK_MENU_HPP

#include "graphics/menu.hpp"

namespace view {

class PazaakMenu : public graphics::Menu
{
  public:

    PazaakMenu(const graphics::Size& size, const std::string& menu_info_file, Display display);

  protected:

    virtual void setFocus(const std::shared_ptr<graphics::Drawable> newly_selected_item, bool play_sound);
    void previousViewEvent();

  private:

    std::shared_ptr<graphics::Animation> m_logo;
};

}

#endif // PAZAAK_MENU_HPP
