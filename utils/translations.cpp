#include "translations.hpp"

#include "utils/logging/easylogging++.h"

namespace utils {

std::unique_ptr<Translations> Translations::s_instance;

void Translations::init(const std::string &translations_path, const std::string &language_file)
{
  if(s_instance)
    return;

  s_instance.reset( new Translations(translations_path, language_file) );
}

Translations::Translations(const std::string& translations_path, const std::string &language_file)
  : Configuration{ translations_path, {language_file} }
{}

const std::string& Translations::translate(const std::string& key)
{
  if(!s_instance)
  {
    LOG(ERROR) << "Can't translate with no Translations manager!";
    static const std::string error {};
    return error;
  }

  return s_instance->get(key);
}

}
