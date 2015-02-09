#include "translations.hpp"

#include "utils/logging/easylogging++.h"
#include "utils/files.hpp"

namespace utils {

Translations::Translations(const std::string& translations_path, const std::string& current_language)
  : m_current_language {current_language}
{
  const std::string translation_file_path {utils::file::ensureDirEnd(translations_path) + current_language + ".conf"};
  LOG(DEBUG) << "Loading translations from " << translation_file_path;
  loadConfig( translation_file_path );
}

}
