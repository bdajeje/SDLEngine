#ifndef MENU_HPP
#define MENU_HPP

#include <chrono>
#include <string>
#include <vector>

#include "graphics/size.hpp"
#include "graphics/text.hpp"
#include "graphics/view.hpp"
#include "graphics/vlayout.hpp"

namespace graphics {

class Menu : public graphics::View
{
  public:

    enum class Display { Vertically, Horizontally };

    Menu(const graphics::Size& size, const std::string& menu_info_file,
         const std::vector<std::string>& texts, const std::string& text_info_file,
         Display display = Display::Vertically, const std::string& background_info_file = {});

    const std::shared_ptr<graphics::Text>& selectedItem() const;

    virtual void newEvent( const SDL_Event& event );

    void setChangeSelectionSound( const std::string& file ) { m_change_selection_sound = file; }

  protected:

    /* Triggered for keyboard event */
    void keyboardChangeSelection(SDL_Keycode key);

    /* When selected menu item changes, call this method to update the UI */
    virtual void setFocus(const std::shared_ptr<graphics::Text>& newly_selected_item);

  protected:

    std::shared_ptr<graphics::VLayout> m_menu;
    std::vector<std::shared_ptr<graphics::Text>> m_items;

    // Currently selected/focused item position in m_items
    size_t m_selected_item_pos {0};

    // Sounds
    std::string m_change_selection_sound;

    // Protect against repeated too fast keyboard events
    std::chrono::microseconds last_keyboard_change {0};
    static const std::chrono::microseconds mimimum_keyboard_time_repeat;
};

}

#endif // MENU_HPP
