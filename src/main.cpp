#include <iostream>

#include "ExampleRegistry.h"
#include "version.h"

void menu() {
  auto& registry = ExampleRegistry::instance();
  const auto& data = registry.getAll();

  int gIndex = 1;
  std::vector<std::string> groups;

  for (const auto& [group, _] : data) {
    std::cout << gIndex++ << ". " << group << "\n";
    groups.push_back(group);
  }

  int gChoice;
  std::cin >> gChoice;

  const auto& selectedGroup = groups[gChoice - 1];
  const auto& examples = data.at(selectedGroup);

  int eIndex = 1;
  std::vector<std::string> names;

  for (const auto& [name, _] : examples) {
    std::cout << eIndex++ << ". " << name << "\n";
    names.push_back(name);
  }

  int eChoice;
  std::cin >> eChoice;

  auto example = registry.create(selectedGroup, names[eChoice - 1]);

  example->run();
}

int main(int argc, char* argv[]) {
  std::cout << std::endl;
  if (__cplusplus == 202302L)
    std::cout << "C++23";
  else if (__cplusplus == 202002L)
    std::cout << "C++20";
  else if (__cplusplus == 201703L)
    std::cout << "C++17";
  else if (__cplusplus == 201402L)
    std::cout << "C++14";
  else if (__cplusplus == 201103L)
    std::cout << "C++11";
  else if (__cplusplus == 199711L)
    std::cout << "C++98";
  else
    std::cout << "pre-standard C++ or an unknown version: " << __cplusplus;
  std::cout << "\n";
  std::cout << APP_NAME << " v" << APP_VERSION << std::endl;
  std::cout << APP_DESCRIPTION << std::endl;
  return 0;
}