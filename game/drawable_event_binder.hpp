#ifndef DRAWABLE_EVENT_BINDER_HPP
#define DRAWABLE_EVENT_BINDER_HPP

#include <memory>

#include "game/event_binder.hpp"

namespace graphics {
  class Drawable;
}

namespace event {

class DrawableEventBinder : public event::EventBinder<const std::shared_ptr<graphics::Drawable>>
{};

}

#endif // DRAWABLE_EVENT_BINDER_HPP
