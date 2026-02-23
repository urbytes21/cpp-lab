#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

#include "ExampleRegistry.h"
#include "version.h"

int readChoice() {
  int x;
  while (!(std::cin >> x)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input. Try again: ";
  }
  // Clear leftover newline from input buffer
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return x;
}

void runMenu() {
  ExampleRegistry& registry = ExampleRegistry::instance();
  const auto& data = registry.getAll();

  while (true) {
    std::cout << "\n========================================\n";
    std::cout << "         CPP LAB - Examples Menu        \n";
    std::cout << "========================================\n";

    if (data.empty()) {
      std::cout << "No examples registered.\n";
      return;
    }

    // Group
    int gIndex = 1;
    std::vector<std::string> groups;

    for (const auto& [group, _] : data) {
      groups.push_back(group);
    }

    // sort
    std::sort(groups.begin(), groups.end());
    for (const auto& group : groups) {
      std::cout << gIndex++ << ". " << group << "\n";
    }
    std::cout << "0. Exit\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Enter choice: ";

    int gChoice = readChoice();
    if (gChoice == 0) {
      std::cout << "\n--- Exit ---\n";
      break;
    }

    if (gChoice < 1 || gChoice > groups.size()) {
      std::cout << "Invalid group choice\n";
      continue;
    }

    try {
      // Sub-group
      const auto& selectedGroup = groups[gChoice - 1];
      const auto& examples = data.at(selectedGroup);

      int eIndex = 1;
      std::vector<std::string> names;

      for (const auto& [name, _] : examples) {
        std::cout << eIndex++ << ". " << name << "\n";
        names.push_back(name);
      }
      std::cout << "0. Back\n";
      std::cout << "----------------------------------------\n";
      std::cout << "Enter choice: ";

      int eChoice = readChoice();
      if (eChoice == 0) {
        continue;
      }

      if (eChoice < 1 || eChoice > names.size()) {
        std::cout << "Invalid example choice\n";
        continue;
      }

      auto example = registry.create(selectedGroup, names[eChoice - 1]);
      if (example != nullptr) {
        std::cout << "\n--- Running Example [" << example->name() << "] ["
                  << example->description() << "]---\n\n";
        example->execute();
        std::cout << "\n--- Finished ---\n";
        std::cout << "Press any key to continue ...\n";
        std::cin.get();
      }
    } catch (std::out_of_range& e) {
      std::cout << "\nError" << e.what();
      std::cout << "\nInvalid example. Try again.\n";
    }
  }
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
  runMenu();
  return 0;
}