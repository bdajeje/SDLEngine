#ifndef TRANSLATIONS_HPP
#define TRANSLATIONS_HPP

#include <map>
#include <memory>
#include <string>

#include "utils/configuration/configuration.hpp"

namespace utils {

class Translations : public Configuration
{
  public:

    static void init(const std::string& translations_path, const std::string& language);
    static const std::string& translate(const std::string& key);

  private:

    Translations(const std::string& translations_path, const std::string& language);

  private:

    static std::unique_ptr<Translations> s_instance;
};

}

#endif // TRANSLATIONS_HPP
