#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <map>
#include <string>
#include <vector>

namespace utils {

class Configuration
{
  public:

    Configuration( const std::string& config_path, const std::vector<std::string>& files );

  private:

    void loadConfig(const std::string& file_path);

  private:

    std::string m_config_path;
    std::map<std::string, std::string> m_configurations;
};

}

#endif // CONFIGURATION_HPP
