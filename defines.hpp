#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <string>

static const std::string Resources_folder { "resources/" };
static const std::string Images_folder { "images/" };

struct Size
{
  uint width;
  uint height;
};

struct Position
{
  int x;
  int y;
};

#endif // DEFINES_HPP
