#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <map>
#include <string>
#include <vector>

namespace utils {

class Configuration
{
  public:

    /*! Default constructor */
    Configuration() = default;

    /*! Constructor, loads all configs file under a specific directory
     * \param dir_path - directory path where to find configuration files to load
     * \note configuration files have '.conf' extension
     */
    Configuration(const std::string& dir_path);

    /*! Constructor, loads several files from paths
     * \param filepaths - to load
     */
    Configuration(const std::vector<std::string>& filepaths);

    /*! Constructor, loads several files from file paths
     * \param filepath  - common filepath for all input files
     * \param filenames - names of files to load
     */
    Configuration(std::string filepath, const std::vector<std::string>& filenames);

    const std::string& get(const std::string& config_key) const;

    void loadConfig(const std::string& file_path);

  private:

    std::map<std::string, std::string> m_configurations;
};

}

#endif // CONFIGURATION_HPP
