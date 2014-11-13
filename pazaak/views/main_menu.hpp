#ifndef PAZAAK_MAIN_MENU_HPP
#define PAZAAK_MAIN_MENU_HPP

#include <chrono>

#include "graphics/size.hpp"
#include "graphics/text.hpp"
#include "graphics/view.hpp"
#include "graphics/vlayout.hpp"

namespace view {

class MainMenu final : public graphics::View
{
  public:

    MainMenu(const graphics::Size& size);

    const std::shared_ptr<graphics::Text>& selectedItem() const;

    void newEvent( const SDL_Event& event );

  private:

    /* When selected menu item changes, call this method to update the UI */
    void setFocus(const std::shared_ptr<graphics::Text>& newly_selected_item);

    /* Triggered for keyboard event */
    void keyboardChangeSelection(SDL_Keycode key);

  private:

  // Specific to main menu
    std::shared_ptr<graphics::Animation> m_logo;

  // General to any menu
    std::shared_ptr<graphics::VLayout> m_menu;
    std::vector<std::shared_ptr<graphics::Text>> m_items;

    // Currently selected/focused item position in m_items
    size_t m_selected_item_pos {0};

    std::chrono::microseconds last_keyboard_change {0};
    static const std::chrono::microseconds mimimum_keyboard_time_repeat;
};

}

#endif // PAZAAK_MAIN_MENU_HPP
