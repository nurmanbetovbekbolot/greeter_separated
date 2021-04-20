#include <iostream>
#include <string>
#include <unordered_map>

#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include "cxxopts-wrapper.h"

namespace greeter {
static const std::string GREETER_VERSION = "1.0.0";

/**  Language codes to be used with the Greeter class */
enum class LanguageCode {
  EN,
  DE,
  ES,
  FR
};

/**
 * @brief A class for saying hello in multiple languages
 */
class Greeter
{
  std::string _name;

public:
  /**
   * @brief Creates a new greeter
   * @param name the name to greet
   */
  Greeter(std::string name) : _name{ name } {}

  /**
   * @brief Creates a localized string containing the greeting
   * @param lang the language to greet in
   * @return a string containing the greeting
   */
  std::string greet(LanguageCode lang = LanguageCode::EN) const;
};

}// namespace greeter

using namespace greeter;

std::string Greeter::greet(LanguageCode lang) const
{
  switch (lang) {
  default:
  case LanguageCode::EN:
    return fmt::format("Hello, {}!", _name);
  case LanguageCode::DE:
    return fmt::format("Hallo {}!", _name);
  case LanguageCode::ES:
    return fmt::format("¡Hola {}!", _name);
  case LanguageCode::FR:
    return fmt::format("Bonjour {}!", _name);
  }
}

// TODO Diskutieren, ob https://github.com/docopt/docopt.cpp besser ist

/////////////////////////////////////////////////

int main(int argc, char **argv)
{
  const std::unordered_map<std::string, greeter::LanguageCode> languages{
    { "en", greeter::LanguageCode::EN },
    { "de", greeter::LanguageCode::DE },
    { "es", greeter::LanguageCode::ES },
    { "fr", greeter::LanguageCode::FR },
  };

  cxxopts::Options options{ *argv, "A program to welcome the world!" };

  std::string language;
  std::string name;

  // clang-format off
  options.add_options()
           ("h,help", "Show help")
           ("v,version", "Print the current version number")
           ("n,name", "Name to greet", cxxopts::value(name)->default_value("World"))
           ("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
    ;
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  if (result["version"].as<bool>()) {
    std::cout << "Greeter, version " << GREETER_VERSION << std::endl;
    return 0;
  }

  auto langIt = languages.find(language);
  if (langIt == languages.end()) {
  // if(not languages.contains(language)) { // contains ab C++20 möglich
    std::cerr << "unknown language code: " << language << std::endl;
    return 1;
  }

  greeter::Greeter greeter(name);
  std::cout << greeter.greet(langIt->second) << std::endl;

  spdlog::info("{}\n", greeter.greet(langIt->second));

  // TODO Code oben restrukturieren
}