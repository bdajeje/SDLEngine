#include "progress_bar.hpp"

namespace graphics {

ProgressBar::ProgressBar(const utils::Configuration& info, const SDL_Rect& parent)
  : Drawable(info, parent)
{
  try
  {
    // Default values
    m_min_value     = std::stoi(info.get( info::MinValue ));
    m_max_value     = std::stoi(info.get( info::MaxValue ));
    m_current_value = std::stoi(info.get( info::CurrentValue ));
  }
  catch(const std::exception& e)
  {
    LOG(ERROR) << "Bad progress bar info file: " << e.what();
  }
}

}
