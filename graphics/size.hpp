#ifndef SIZE_HPP
#define SIZE_HPP

namespace graphics {

/* Represents a 2D object size with a widht and height */
struct Size
{
  Size(int width, int height)
    : w(width)
    , h(height)
  {}

  // We use integers and not unsigned integers because SDL uses integers in SDL_Rect
  int w {0}; // Width
  int h {0}; // Height
};

}

#endif // SIZE_HPP
