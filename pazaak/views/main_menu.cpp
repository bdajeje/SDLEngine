#include "main_menu.hpp"

#include "sounds/sounds_manager.hpp"
#include "utils/translations.hpp"

#include "pazaak/musics.hpp"
#include "pazaak/translations.hpp"

namespace view {

MainMenu::MainMenu(const graphics::Size& size)
  : PazaakMenu{ size, "main_menu/menu",
              { utils::Translations::translate(translations::MainMenu::Play),
                utils::Translations::translate(translations::MainMenu::Settings),
                utils::Translations::translate(translations::MainMenu::Quit) }, "main_menu/text",
                Display::Vertically }
{
  // Play a nice music :)
  sounds::SoundsManager::playMusic( music::MainMenu, -1 );
}

}
