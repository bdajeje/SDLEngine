#ifndef KEYBOARD_EVENT_BINDER_HPP
#define KEYBOARD_EVENT_BINDER_HPP

#include <SDL2/SDL.h>

#include "game/event_binder.hpp"

namespace event {

class KeyboardEventBinder : public event::EventBinder<SDL_Keycode>
{};

}

#endif // KEYBOARD_EVENT_BINDER_HPP
