#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL2/SDL.h>

#include "graphics/position.hpp"
#include "graphics/size.hpp"
#include "graphics/view.hpp"
#include "graphics/manager/font_manager.hpp"
#include "graphics/manager/texture_manager.hpp"
#include "sounds/sounds_manager.hpp"
#include "utils/translations.hpp"

struct Events
{
  Uint32 MenuSelectItem {(Uint32)-1};
  Uint32 PreviousView   {(Uint32)-1};
};

/* Helper structure to easily initialize the Engine */
struct EngineConfiguration
{
  /* Application title */
  std::string title;

  /* Path to folder containing configuration files to load */
  std::string configs_path;

  /* Path to folder containing translations files to load */
  std::string translations_path;

  /* Path to folder containing images */
  std::string images_path;

  /* Path to folder containing fonts */
  std::string fonts_path;

  /* Path to folder containing musics */
  std::string musics_path;

  /* Path to folder containing sounds */
  std::string sounds_path;

  /* Size of the window */
  graphics::Size size;
};

/* Game Engine main class */
class Engine
{
  public:

    /* Static method to call in order to initialize the engine
     * \param configurations - initial configs to start and load the game engine
     * \throw on init error
     */
    static void init(const EngineConfiguration& configurations);

    /* Clean engine resources */
    static void clean();

    static void clearScreen();
    static void render(graphics::ViewPtr view);
    static graphics::Size windowSize();
    static SDL_Renderer* renderer() { return s_instance->m_renderer; }
    static graphics::Position mousePosition();

    // Managers access
    static utils::Translations& translations() { return s_instance->m_translations_manager; }
    static graphics::TextureManager& textures() { return s_instance->m_textures_manager; }
    static graphics::FontManager& fonts() { return s_instance->m_fonts_manager; }
    static sounds::SoundsManager& sounds() { return s_instance->m_sounds_manager; }

    // Events
    static const Events& events() { return s_instance->m_events; }

  private:

    /* Hidden constructor */
    Engine(const EngineConfiguration& configurations, SDL_Window* window, SDL_Renderer* renderer);

  private:

    // Specific events
    Events m_events;

    /* Managers */
    utils::Configuration m_configurations;
    utils::Translations m_translations_manager;
    graphics::TextureManager m_textures_manager;
    graphics::FontManager m_fonts_manager;
    sounds::SoundsManager m_sounds_manager;

    /* SDL objects */
    SDL_Window* m_window {nullptr};
    SDL_Renderer* m_renderer {nullptr};

    /* Game Engine unique instance */
    static std::unique_ptr<Engine> s_instance;
};

#endif // ENGINE_HPP
