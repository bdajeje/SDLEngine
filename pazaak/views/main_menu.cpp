#include "main_menu.hpp"

#include "defines.hpp"
#include "engine.hpp"
#include "graphics/animation.hpp"
#include "graphics/manager/font_manager.hpp"
#include "graphics/manager/texture_manager.hpp"
#include "utils/translations.hpp"

#include "pazaak/textures.hpp"
#include "pazaak/translations.hpp"

namespace view {

const std::chrono::microseconds MainMenu::mimimum_keyboard_time_repeat {100000};

MainMenu::MainMenu(const graphics::Size& size)
  : View{ graphics::Position{0,0}, size }
{
  // Background
  utils::Configuration background_info {IMAGE_INFO_PATH, {"main_menu/background"}};
  addObject( std::make_shared<graphics::Drawable>(background_info, destination() ) );

  // Menu layout
  utils::Configuration menu_info {IMAGE_INFO_PATH, {"main_menu/menu"}};
  m_menu = std::make_shared<graphics::VLayout>(menu_info, destination());
  addObject(m_menu);

  // Menu items
  utils::Configuration text_info {IMAGE_INFO_PATH, {"main_menu/text"}};
  m_items.emplace_back( std::make_shared<graphics::Text>(utils::Translations::translate(translations::MainMenu::Play), text_info ) );
  m_items.emplace_back( std::make_shared<graphics::Text>(utils::Translations::translate(translations::MainMenu::Settings), text_info ) );
  m_items.emplace_back( std::make_shared<graphics::Text>(utils::Translations::translate(translations::MainMenu::Quit), text_info ) );

  // Add menu items to layout
  for(auto& item : m_items)
    m_menu->addObject( item );

  // Logo
  utils::Configuration logo_info {IMAGE_INFO_PATH, {"main_menu/logo"}};
  m_logo = std::make_shared<graphics::Animation>( logo_info, destination() );
  addAnimation( m_logo );

  setFocus( selectedItem() );
}

void MainMenu::setFocus(const std::shared_ptr<graphics::Text>& newly_selected_item)
{
  for( auto& item : m_items )
    item->setSelected( item == newly_selected_item );

  // Place logo on current selected menu item
  static const int x_margin = 20;
  m_logo->setPosition( newly_selected_item->posX() - m_logo->width()- x_margin, newly_selected_item->posY() );
}

void MainMenu::newEvent( const SDL_Event& event )
{
  // Handles only key up or down
  if( !event.type == SDL_KEYDOWN )
    return;

  keyboardChangeSelection(event.key.keysym.sym);
}

void MainMenu::keyboardChangeSelection(SDL_Keycode key)
{
  if( key != SDLK_DOWN && key != SDLK_UP )
    return;

  // For item selection change, check the last time we did it to prevent too fast updates
  const auto now = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::high_resolution_clock::now().time_since_epoch() );
  if( now - last_keyboard_change < mimimum_keyboard_time_repeat )
    return;
LOG(DEBUG) << now.count() << " - " << last_keyboard_change.count() << " = " << ((now-last_keyboard_change).count());
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

const std::shared_ptr<graphics::Text>& MainMenu::selectedItem() const
{
  return m_items[m_selected_item_pos];
}

}
