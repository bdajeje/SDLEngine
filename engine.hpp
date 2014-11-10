#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL2/SDL.h>

#include "graphics/size.hpp"
#include "graphics/view.hpp"

class Engine
{
  public:

    static void init(const std::string& title, int width, int height,
                     const std::string& configs_path, const std::vector<std::string>& config_files,
                     const std::string& translations_path, const std::string& language_file,
                     const std::string& images_path, const std::string& fonts_path,
                     const std::string& musics_path, const std::string& sounds_path);

    static void clean();

    //std::unique_ptr<Engine>& instance() { return s_instance; }

    static void clearScreen();
    static void render(graphics::ViewPtr view);
    static graphics::Size windowSize();

    // \todo to remove
    static SDL_Renderer* renderer() { return s_instance->m_renderer; }

  private:

    Engine(const std::string& configs_path, const std::vector<std::string>& config_files,
           SDL_Window* window, SDL_Renderer* renderer);

  private:

    utils::Configuration m_configurations;
    graphics::Size m_window_size;
    SDL_Window* m_window {nullptr};
    SDL_Renderer* m_renderer {nullptr};

    static std::unique_ptr<Engine> s_instance;
};

#endif // ENGINE_HPP
