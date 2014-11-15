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
    size_t selectedPosition() const { return m_selected_item_pos; }

    virtual void newEvent( const SDL_Event& event );

    void setChangeItemSound( const std::string& file ) { m_change_selection_sound = file; }
    void setChooseItemSound( const std::string& file ) { m_select_item_sound = file; }
    void setFocusToPosition( size_t item_offest );

  protected:

    /* Pre calculate items min/max borders to speed up mouse move event processing */
    void computeItemBorders();

    /* Find position of a given item inside m_items
     * If the item couldn't be found, return an invalid position
     */
    //size_t itemOffset(const std::shared_ptr<graphics::Text>& wanted_item);

    /* Triggered for keyboard event */
    void keyboardChangeSelection(SDL_Keycode key);

    /* When selected menu item changes, call this method to update the UI */
    virtual void setFocus(const std::shared_ptr<graphics::Text>& newly_selected_item);

    /* Triggered when a menu item is choosen */
    void chooseItem();

    /* Handle mouse move event */
    void mouseMove();

    /* Handle mouse click event */
    void mouseClick();

    /* Find item under mouse
     * return offset inside m_items of the item under the mouse or m_items.size()+1 if no item under mouse
     */
    size_t itemUnderMouse() const;

    /* Get item position taking into account the menu position where the item is */
    int itemPosX(const std::shared_ptr<graphics::Text>& item) const;
    int itemPosY(const std::shared_ptr<graphics::Text>& item) const;

  protected:

    std::shared_ptr<graphics::VLayout> m_menu;
    std::vector<std::shared_ptr<graphics::Text>> m_items;

    // Currently selected/focused item position in m_items
    size_t m_selected_item_pos {0};

    // Sounds
    std::string m_change_selection_sound;
    std::string m_select_item_sound;

    // Menu item borders
    Position m_item_min_limits;
    Position m_item_max_limits;

    // Protect against repeated too fast keyboard events
    std::chrono::microseconds last_keyboard_change {0};
    static const std::chrono::microseconds mimimum_keyboard_time_repeat;
};

}

#endif // MENU_HPP
