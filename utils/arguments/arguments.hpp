#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <boost/lexical_cast.hpp>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

#include "utils/logging/easylogging++.h"

namespace utils {

class Arguments
{
  public:

    Arguments(int argc, char* argv[]);

    // Get an argument
    // \param position of the argument in the argument list
    // \return Converted argument to T type at given position
    // \throw if position out of bound or can't convert to desired type
    template<class T>
    T get(size_t position) const
    {
      if( position >= m_arguments.size() )
        throw std::range_error("Requesting argument at position " + std::to_string(position) +
                               " but there are only " + std::to_string(m_arguments.size()) + " arguments");

      try { return boost::lexical_cast<T>( m_arguments[position] ); }
      catch(...) {
        LOG(ERROR) << "Can't cast argument at " << position;
        throw std::bad_cast();
      }
    }

    // Same as previous one but don't throw, instead return default_value if anything goes wrong
    template<class T>
    T get(size_t position, T default_value) const
    {
      if( position >= m_arguments.size() )
      {
        LOG(ERROR) << "Requesting argument at position " << position << " but there are only " << m_arguments.size() << " arguments";
        return default_value;
      }

      try { return boost::lexical_cast<T>( m_arguments[position] ); }
      catch(...) {
        LOG(ERROR) << "Can't cast argument at " << position;
        return default_value;
      }
    }

  private:

    void parseArgs(int argc, char* argv[]);

  private:

    std::vector<std::string> m_arguments;
};

}

#endif // ARGUMENTS_HPP
