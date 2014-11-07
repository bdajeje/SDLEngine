#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SDL2/SDL.h>

#include <map>
#include <memory>
#include <string>

namespace graphics {

class TextureManager final
{
  public:

    static void init(const std::string& textures_path);

    ~TextureManager();

    static SDL_Texture* get(const std::string& path, SDL_Renderer* renderer);

  private:

    TextureManager(const std::string& textures_path);

    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);

  private:

    std::string m_textures_path;
    std::map<std::string, SDL_Texture*> m_textures;

    static std::unique_ptr<TextureManager> s_instance;
};

}

#endif // TEXTURE_MANAGER_HPP
