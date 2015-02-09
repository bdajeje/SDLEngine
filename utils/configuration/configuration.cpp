#include "configuration.hpp"

#include <boost/algorithm/string.hpp>

#include "utils/files.hpp"
#include "utils/logging/easylogging++.h"

namespace utils {

Configuration::Configuration(const std::string& dir_path)
  : Configuration( utils::file::listFilesInDir(dir_path, ".*\.conf") )
{}

Configuration::Configuration(const std::vector<std::string>& filepaths)
{
  for( const auto& file : filepaths )
    loadConfig( file );
}

Configuration::Configuration(std::string filepath, const std::vector<std::string>& filenames)
{
  filepath = utils::file::ensureDirEnd(filepath);
  for( const auto& filename : filenames )
    loadConfig( filepath + filename );
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

const std::string& Configuration::get(const std::string& config_key) const
{
  auto found = m_configurations.find(config_key);
  if(found == m_configurations.end())
  {
    static const std::string error;
    return error;
  }

  return found->second;
}

}
