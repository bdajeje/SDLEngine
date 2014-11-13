#include "menu.hpp"

#include "defines.hpp"

namespace graphics {

const std::chrono::microseconds Menu::mimimum_keyboard_time_repeat {100000};

Menu::Menu(const graphics::Size& size, const std::string& menu_info_file,
           const std::vector<std::string>& texts, const std::string& text_info_file,
           Display /*display*/, const std::string& background_info_file)
  : View{ graphics::Position{0,0}, size }
{
  // Background
  if( !background_info_file.empty() )
  {
    utils::Configuration background_info {IMAGE_INFO_PATH, {background_info_file}};
    addObject( std::make_shared<graphics::Drawable>(background_info, destination() ) );
  }

  // Menu layout
  // \todo display input variable is actually not handled (we always create vertical menu yet)
  utils::Configuration menu_info {IMAGE_INFO_PATH, {menu_info_file}};
  m_menu = std::make_shared<graphics::VLayout>(menu_info, destination());
  addObject(m_menu);

  // Menu items
  utils::Configuration text_info {IMAGE_INFO_PATH, {text_info_file}};
  for( const auto& text : texts )
    m_items.emplace_back( std::make_shared<graphics::Text>(text, text_info ) );

  // Add menu items to layout
  for(auto& item : m_items)
    m_menu->addObject( item );

  setFocus( selectedItem() );
}

void Menu::newEvent( const SDL_Event& event )
{
  // Handles only key up or down
  if( !event.type == SDL_KEYDOWN )
    return;

  keyboardChangeSelection(event.key.keysym.sym);
}

void Menu::keyboardChangeSelection(SDL_Keycode key)
{
  if( key != SDLK_DOWN && key != SDLK_UP )
    return;

  // For item selection change, check the last time we did it to prevent too fast updates
  const auto now = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::high_resolution_clock::now().time_since_epoch() );
  if( now - last_keyboard_change < mimimum_keyboard_time_repeat )
    return;

  last_keyboard_change = now;

  switch(key)
  {
    case SDLK_DOWN:
      m_selected_item_pos++;
      if( m_selected_item_pos >= m_items.size())
        m_selected_item_pos = 0;
      break;
    case SDLK_UP:
      if( m_selected_item_pos == 0)
        m_selected_item_pos = m_items.size() - 1;
      else
        m_selected_item_pos--;
      break;
    default:
      return;
  }

  setFocus( selectedItem() );
}

const std::shared_ptr<graphics::Text>& Menu::selectedItem() const
{
  return m_items[m_selected_item_pos];
}

void Menu::setFocus(const std::shared_ptr<graphics::Text>& newly_selected_item)
{
  for( auto& item : m_items )
    item->setSelected( item == newly_selected_item );
}

}
