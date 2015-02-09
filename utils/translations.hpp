#ifndef TRANSLATIONS_HPP
#define TRANSLATIONS_HPP

#include <string>

#include "utils/configuration/configuration.hpp"

namespace utils {

class Translations final : public Configuration
{
  public:

    Translations(const std::string& translations_path, const std::string& current_language = "en");

  private:

    std::string m_current_language;
};

}

#endif // TRANSLATIONS_HPP
