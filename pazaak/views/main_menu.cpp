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

MainMenu::MainMenu(const graphics::Size& size)
  : View{ graphics::Position{0,0}, size }
{
  // Background
  utils::Configuration background_info {IMAGE_INFO_PATH, {"main_menu/background"}};
  addObject( std::make_shared<graphics::Drawable>(background_info, destination() ) );

  // Menu texts
  utils::Configuration text_info {IMAGE_INFO_PATH, {"main_menu/text"}};
  utils::Configuration menu_info {IMAGE_INFO_PATH, {"main_menu/menu"}};
  m_menu = std::make_shared<graphics::VLayout>(menu_info, destination());
  m_play_text = std::make_shared<graphics::Text>(utils::Translations::translate(translations::MainMenu::Play), text_info );
  m_menu->addObject( m_play_text );
  m_settings_text = std::make_shared<graphics::Text>(utils::Translations::translate(translations::MainMenu::Settings), text_info );
  m_menu->addObject( m_settings_text );
  m_quit_text = std::make_shared<graphics::Text>(utils::Translations::translate(translations::MainMenu::Quit), text_info );
  m_menu->addObject( m_quit_text );
  addObject(m_menu);

  // Get normal color from text info
  // \todo get those value from info file (in a generic Menu class)
  m_normal_color   = m_play_text->color();
  m_selected_color = SDL_Color{252,199,91,255};

  // Logo
  utils::Configuration logo_info {IMAGE_INFO_PATH, {"main_menu/logo"}};
  m_logo = std::make_shared<graphics::Animation>( logo_info, destination() );
  addAnimation( m_logo );

  setFocus(m_play_text);
}

void MainMenu::setFocus(std::shared_ptr<graphics::Text>& to_select)
{
  // Place logo on current selected menu item
  static const int x_margin = 20;
  m_logo->setPosition( to_select->posX() - m_logo->width()- x_margin, to_select->posY() );

  // Set a new color for the selected item
  // \todo update this to allow generic usages
  m_play_text->setColor( (to_select == m_play_text) ? m_selected_color : m_normal_color );
  m_settings_text->setColor( (to_select == m_settings_text) ? m_selected_color : m_normal_color );
  m_quit_text->setColor( (to_select == m_quit_text) ? m_selected_color : m_normal_color );
}

}
