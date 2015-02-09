#ifndef PROGRESS_BAR_HPP
#define PROGRESS_BAR_HPP

#include "graphics/drawable.hpp"

namespace graphics {

namespace info {
  static const std::string MinValue {"min_value"};
  static const std::string MaxValue {"max_value"};
  static const std::string CurrentValue {"current_value"};
}

class ProgressBar final : public Drawable
{
  public:

    ProgressBar(const utils::Configuration& info, const SDL_Rect& parent);

  private:

    int m_min_value;
    int m_max_value;
    int m_current_value;
};

}

#endif // PROGRESS_BAR_HPP
