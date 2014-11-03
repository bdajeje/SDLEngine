#ifndef VIEW_HPP
#define VIEW_HPP

#include <SDL2/SDL.h>

#include <map>
#include <memory>
#include <vector>
#include <string>

#include "drawable.hpp"

class View
{
  public:

    View();
    ~View();

    void draw();

  protected:

    void addObject(std::shared_ptr<Drawable> drawable);

    SDL_Surface* loadSurface(const std::string& path);

  private:

    // Original surface pointers are here
    std::map<std::string, SDL_Surface*> m_surfaces;

    std::vector<std::shared_ptr<Drawable>> m_objects;
};

typedef std::shared_ptr<View> ViewPtr;

#endif // VIEW_HPP
