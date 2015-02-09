#include "main_menu.hpp"

#include "engine.hpp"
#include "defines.hpp"
#include "sounds/sounds_manager.hpp"
#include "utils/translations.hpp"

#include "pazaak/musics.hpp"
#include "pazaak/translations.hpp"

namespace view {

MainMenu::MainMenu(const graphics::Size& size)
  : PazaakMenu{ size, "main_menu/menu", Display::Vertically }
{
  // Play a nice music :)
  Engine::sounds().playMusic( music::MainMenu, -1 );

  utils::Configuration text_info {IMAGE_INFO_PATH, {"main_menu/text"}};
  static const std::vector<std::string> texts { Engine::translations().get(translations::MainMenu::Solo),
                                                Engine::translations().get(translations::MainMenu::Multi),
                                                Engine::translations().get(translations::MainMenu::Settings),
                                                Engine::translations().get(translations::MainMenu::Quit) };
  for( const auto& text : texts )
    addMenuItem( std::make_shared<graphics::Text>(text, text_info) );

  setFocus(m_items.front(), false);

  // Key events
  KeyboardEventBinder::bind( SDLK_ESCAPE, std::bind(&MainMenu::selectQuit, this) );

  // Items events
  // \todo For now we stupidly send an event when any item is selected and the game (pazaak.hpp) does the job depending on which item is currently selected
  //       This sucks because the game has to do things he shouldn't. Find a solution when this MainMenu directly sends what to do exactly
  for( size_t i = 0; i < m_items.size(); ++i )
    DrawableEventBinder::bind(m_items[i], std::bind(&MainMenu::sendChooseItemEvent, this));
}

void MainMenu::selectQuit()
{
  setFocusToPosition( m_items.size() - 1 );
}

void MainMenu::sendChooseItemEvent()
{
  SDL_Event event {Engine::events().MenuSelectItem};
  SDL_PushEvent(&event);
}

}
