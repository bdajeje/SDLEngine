#include "configuration.hpp"

#include <boost/algorithm/string.hpp>

#include "utils/files.hpp"
#include "utils/logging/easylogging++.h"

namespace utils {

Configuration::Configuration(const std::string& config_path, const std::vector<std::string>& files)
  : m_config_path(config_path)
{
  if( m_config_path.back() != '/' )
    m_config_path += '/';

  for( const auto& file : files )
    loadConfig( config_path + file );

  for( auto conf : m_configurations )
    LOG(DEBUG) << "'" << conf.first << "' '" << conf.second << "'";
}

void Configuration::loadConfig(const std::string& file_path)
{
  std::string content;
  if( !utils::file::read(file_path, content) )
  {
    LOG(ERROR) << "Can't read file: " << file_path;
    return;
  }

  std::vector<std::string> lines;
  boost::algorithm::split(lines, content, boost::is_any_of("\n"));

  for( auto& line : lines )
  {
    // Remove possible trailing spaces
    boost::algorithm::trim(line);

    // Ignore comment line
    if( boost::algorithm::starts_with(line, "#") )
      continue;

    // Split key and value
    auto pos = line.find('=');
    if(pos == std::string::npos)
      continue;

    auto key   = boost::algorithm::trim_copy(line.substr(0, pos));
    auto value = boost::algorithm::trim_copy(line.substr(pos + 1));
    m_configurations[key] = value;
  }
}

}
