#ifndef POSITION_HPP
#define POSITION_HPP

namespace graphics {

struct Position
{
  Position(int x, int y)
    : x(x)
    , y(y)
  {}

  int x {0};
  int y {0};
};

}

#endif // POSITION_HPP
