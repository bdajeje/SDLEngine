#ifndef PAZAAK_MAIN_MENU_HPP
#define PAZAAK_MAIN_MENU_HPP

#include "graphics/text.hpp"
#include "graphics/size.hpp"
#include "graphics/view.hpp"
#include "graphics/vlayout.hpp"

namespace view {

class MainMenu final : public graphics::View
{
  public:

    MainMenu(SDL_Renderer* renderer, const graphics::Size& size);

  private:

    /* When selected menu item changes, call this method to update the UI */
    void setFocus(std::shared_ptr<graphics::Text>& to_select, SDL_Renderer* renderer);

  private:

    std::shared_ptr<graphics::Animation> m_logo;
    std::shared_ptr<graphics::VLayout> m_menu;
    std::shared_ptr<graphics::Text> m_play_text;
    std::shared_ptr<graphics::Text> m_settings_text;
    std::shared_ptr<graphics::Text> m_quit_text;

    // Currently selected/focused text
    std::shared_ptr<graphics::Text> m_selected_text;

    SDL_Color m_normal_color;
    SDL_Color m_selected_color;
};

}

#endif // PAZAAK_MAIN_MENU_HPP
