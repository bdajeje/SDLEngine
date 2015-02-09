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

    TextureManager(const std::string& textures_path);

    ~TextureManager();

    SDL_Texture* get(const std::string& path);

  private:

    SDL_Texture* loadTexture(const std::string& path);

  private:

    std::string m_textures_path;
    std::map<std::string, SDL_Texture*> m_textures;
};

}

#endif // TEXTURE_MANAGER_HPP
