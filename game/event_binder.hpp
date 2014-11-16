#ifndef EVENT_BINDER_HPP
#define EVENT_BINDER_HPP

#include <functional>
#include <map>

namespace event {

template <class T>
class EventBinder
{
  public:

    typedef std::function<void(EventBinder*)> EventCallback;

    void bind(T trigger, EventCallback funct)
    {
      m_bindings[trigger] = funct;
    }

    bool send(T event_id)
    {
      auto found = m_bindings.find(event_id);
      if( found == m_bindings.end() )
        return false;

      EventCallback callback = m_bindings[event_id];
      callback(this);
      return true;
    }

  private:

    std::map<T, EventCallback> m_bindings;
};

}

#endif // EVENT_BINDER_HPP
