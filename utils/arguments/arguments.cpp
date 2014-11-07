#include "utils/arguments/arguments.hpp"

namespace utils {

Arguments::Arguments(int argc, char* argv[])
{
  parseArgs(argc, argv);
}

void Arguments::parseArgs(int argc, char* argv[])
{
  // Reserve known space
  m_arguments.reserve(argc);

  for( int i = 0; i < argc; ++i )
    m_arguments.emplace_back( argv[i] );
}

}
