#include "main_menu.hpp"

#include "engine.hpp"
#include "sounds/sounds_manager.hpp"
#include "utils/translations.hpp"

#include "pazaak/musics.hpp"
#include "pazaak/translations.hpp"

namespace view {

MainMenu::MainMenu(const graphics::Size& size)
  : PazaakMenu{ size, "main_menu/menu",
              { utils::Translations::translate(translations::MainMenu::Solo),
                utils::Translations::translate(translations::MainMenu::Multi),
                utils::Translations::translate(translations::MainMenu::Settings),
                utils::Translations::translate(translations::MainMenu::Quit) }, "main_menu/text",
                Display::Vertically }
{
  // Play a nice music :)
  sounds::SoundsManager::playMusic( music::MainMenu, -1 );

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
