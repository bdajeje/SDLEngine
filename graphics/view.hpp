#ifndef VIEW_HPP
#define VIEW_HPP

#include <SDL2/SDL.h>

#include <map>
#include <memory>
#include <vector>

#include "drawable.hpp"

namespace graphics {

class View
{
  public:

    View() = default;
    virtual ~View();

    void draw(SDL_Renderer* renderer);

  protected:

    SDL_Texture* getTexture(const std::string& path);
    SDL_Texture* loadTexture(const std::string& path);

    void addObject(std::shared_ptr<Drawable> drawable);

  private:

    std::map<std::string, SDL_Texture*> m_textures;
    std::vector<std::shared_ptr<Drawable>> m_objects;
};

typedef std::shared_ptr<View> ViewPtr;

}

#endif // VIEW_HPP
