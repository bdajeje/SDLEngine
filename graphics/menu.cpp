#include "menu.hpp"

#include "defines.hpp"
#include "engine.hpp"
#include "sounds/sounds_manager.hpp"

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

  // Compute menu item borders to speed up mouse move event (so we don't try to find over which item the mouse is if not inside those borders)
  computeItemBorders();

  setFocus( selectedItem() );
}

void Menu::computeItemBorders()
{
  // No item? Nothing to do
  if( m_items.empty() )
    return;

  // Min Y
  m_item_min_limits.y = itemPosY(m_items.front());

  // Max Y
  const auto& last_item = m_items.back();
  m_item_max_limits.y = itemPosY(last_item) + last_item->height();

  // Min and max X
  const auto& first_item = m_items.front();
  m_item_min_limits.x = itemPosX(first_item);
  m_item_max_limits.x = m_item_min_limits.x + first_item->width();
  int x_first_point, x_last_point;
  const size_t size = m_items.size();
  for( size_t offset = 1; offset < size; ++offset )
  {
    const auto& item = m_items[offset];

    // Min X
    x_first_point = itemPosX(item);
    if( m_item_min_limits.x > x_first_point )
      m_item_min_limits.x = x_first_point;

    // Max X
    x_last_point = x_first_point + item->width();
    if( x_last_point > m_item_max_limits.x )
      m_item_max_limits.x = x_last_point;
  }
}

void Menu::newEvent( const SDL_Event& event )
{
  // Handles only key up or down
  switch(event.type)
  {
    case SDL_KEYDOWN:
    {
      if( event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN )
        keyboardChangeSelection(event.key.keysym.sym);
      else if( event.key.keysym.sym == SDLK_RETURN )
        chooseItem();

      break;
    }
    case SDL_MOUSEMOTION: mouseMove(); break;
    case SDL_MOUSEBUTTONUP: mouseClick(); break;
  }
}

size_t Menu::itemUnderMouse() const
{
  // Get mouse position
  Position mouse_pos = Engine::mousePosition();

  // If not even inside item borders, it can't be over any items
  if( mouse_pos.x < m_item_min_limits.x || mouse_pos.x > m_item_max_limits.x ||
      mouse_pos.y < m_item_min_limits.y || mouse_pos.y > m_item_max_limits.y )
    return m_items.size() + 1;

  // Find over which item is the mouse
  int item_x, item_y;
  size_t offset;
  size_t size = m_items.size();
  for( offset = 0; offset < size; ++offset )
  {
    const auto& item = m_items[offset];
    item_x = itemPosX(item);
    item_y = itemPosY(item);

    if( mouse_pos.x > item_x && mouse_pos.x < (item_x + item->width()) &&
        mouse_pos.y > item_y && mouse_pos.y < (item_y + item->height()) )
      return offset;
  }

  return m_items.size() + 1;
}

int Menu::itemPosX(const std::shared_ptr<graphics::Text>& item) const
{
  return m_menu->posX() + item->posX();
}

int Menu::itemPosY(const std::shared_ptr<graphics::Text>& item) const
{
  return m_menu->posY() + item->posY();
}

void Menu::mouseMove()
{
  size_t item_offset = itemUnderMouse();
  if( item_offset < m_items.size() )
    setFocusToPosition( item_offset );
}

void Menu::mouseClick()
{
  if( itemUnderMouse() )
    chooseItem();
}

//size_t Menu::itemOffset(const std::shared_ptr<graphics::Text>& wanted_item)
//{
//  size_t offset = 0;
//  size_t size   = m_items.size();
//  for( ; offset < size; ++offset )
//  {
//    if( wanted_item == m_items[offset] )
//      break;
//  }

//  return offset;
//}

void Menu::chooseItem()
{
  // Play choose item sound if any
  if( !m_select_item_sound.empty() )
    sounds::SoundsManager::playSound(m_select_item_sound);

  // Send event
  SDL_Event event {Engine::events().MenuSelectItem};
  SDL_PushEvent(&event);
}

void Menu::keyboardChangeSelection(SDL_Keycode key)
{
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

void Menu::setFocusToPosition(size_t item_offest)
{
  // If the offset is already the selected one, return
  if( item_offest == m_selected_item_pos )
    return;
  else if( item_offest >= m_items.size() )
  {
    LOG(ERROR) << "Can't select menu item at position " << item_offest << " when there are only " << m_items.size() << " items";
    return;
  }

  m_selected_item_pos = item_offest;
  setFocus( m_items[item_offest] );
}

void Menu::setFocus(const std::shared_ptr<graphics::Text>& newly_selected_item)
{
  // Update selected item UI
  for( auto& item : m_items )
    item->setSelected( item == newly_selected_item );

  // Play sound
  if( !m_change_selection_sound.empty() )
    sounds::SoundsManager::playSound(m_change_selection_sound);
}

}
