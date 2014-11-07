#ifndef SIZE_HPP
#define SIZE_HPP

namespace graphics {

struct Size
{
  // We use integers and not unsigned integers because SDL uses integers in SDL_Rect
  int w; // Width
  int h; // Height
};

}

#endif // SIZE_HPP
