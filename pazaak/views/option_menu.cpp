#include "option_menu.hpp"

#include "pazaak/translations.hpp"

#include "defines.hpp"
#include "engine.hpp"
#include "graphics/progress_bar.hpp"
#include "utils/translations.hpp"

namespace view {

OptionMenuSetting::OptionMenuSetting(const graphics::Size& size, std::shared_ptr<graphics::Text> title, std::shared_ptr<graphics::Drawable> content)
  : graphics::Menu(size, "option_menu/setting_block", Display::Vertically)
{
  addMenuItem(title);
  addMenuItem(content);
}

OptionMenu::OptionMenu(const graphics::Size& size)
  : PazaakMenu{ size, "main_menu/menu", Display::Vertically}
{
  // Item infos
  utils::Configuration text_info {IMAGE_INFO_PATH, {"main_menu/text"}};
  utils::Configuration progressbar_info {IMAGE_INFO_PATH, {"option_menu/progress_bar"}};
  graphics::Size setting_size {200, 100};

  // Sound settings
  auto sound_title  = std::make_shared<graphics::Text>(Engine::translations().get(translations::OptionMenu::Sound), text_info, destination());
  auto sound_bar    = std::make_shared<graphics::ProgressBar>(progressbar_info, destination());
  auto sound_volume = std::make_shared<OptionMenuSetting>(setting_size, sound_title, sound_bar);

  // Music settings
  auto music_title  = std::make_shared<graphics::Text>(Engine::translations().get(translations::OptionMenu::Music), text_info, destination());
  auto music_bar    = std::make_shared<graphics::ProgressBar>(progressbar_info, destination());
  auto music_volume = std::make_shared<OptionMenuSetting>(setting_size, music_title, music_bar);

  // Back
  auto back = std::make_shared<graphics::Text>(Engine::translations().get(translations::Menu::Back), text_info, destination());

  // Add graphical parts to menu
  addMenuItem( sound_volume );
  addMenuItem( music_volume );
  addMenuItem( back );

  setFocus(m_items.front(), false);

  // Events
  DrawableEventBinder::bind( m_items[2], std::bind(&OptionMenu::previousViewEvent, this) );
}

}
