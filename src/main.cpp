#include <exception>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

#include "ExampleRegistry.h"
#include "Logger.h"
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
    size_t g_index = 1;
    std::vector<std::string> groups;
    groups.reserve(data.size());

    for (const auto& [group, _] : data) {
      groups.push_back(group);
    }

    // sort
    std::sort(groups.begin(), groups.end());
    for (const auto& group : groups) {
      std::cout
          << std::setw(2) << g_index++ << ". " << group
          << "\n";  // use at least 2 characters of space for the next value
    }
    std::cout << g_index << ". Exit\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Enter choice: ";

    size_t g_choice = readChoice();
    if (g_choice == g_index) {
      std::cout << "\n--- Exit ---\n";
      break;
    }

    if (g_choice < 1 || g_choice > groups.size()) {
      std::cout << "Invalid group choice\n";
      continue;
    }

    while (true) {
      try {
        // Sub-group
        const auto& selected_group = groups[g_choice - 1];
        const auto& examples = data.at(selected_group);

        int e_index = 1;
        std::vector<std::string> names;

        for (const auto& [name, _] : examples) {
          std::cout << std::setw(2) << e_index++ << ". " << name << "\n";
          names.push_back(name);
        }
        std::cout << std::setw(2) << e_index << ". Back\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Enter choice: ";

        int e_choice = readChoice();
        // return
        if (e_choice == e_index) {
          break;
        }

        if (e_choice < 1 || e_choice > e_index) {
          std::cout << "Invalid example choice\n";
          continue;
        }

        auto example = registry.create(selected_group, names[e_choice - 1]);
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
}

void printInfo() {
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
}

enum class ApplicationMode {
  kDev,
  kUAT,
  kProd,
};

static ApplicationMode mode = ApplicationMode::kDev;

std::string toString(ApplicationMode m) {
  switch (m) {
    case ApplicationMode::kDev:
      return "dev";
    case ApplicationMode::kUAT:
      return "uat";
    case ApplicationMode::kProd:
      return "prod";
  }
  return "unknown";
}

ApplicationMode parseMode(const std::string& value) {
  if (value == "Dev")
    return ApplicationMode::kDev;
  if (value == "Uat")
    return ApplicationMode::kUAT;
  if (value == "Prod")
    return ApplicationMode::kProd;

  throw std::invalid_argument("Invalid mode: " + value +
                              ". Expected: dev, uat, prod");
}

void handleArg(int argc, const char* const argv[]) {
  // argv[0] = executable
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-mode") {
      if (i + 1 >= argc) {
        std::cerr << "Missing value for -mode\n";
        return;
      }

      std::string value = argv[++i];
      try {
        mode = parseMode(value);
      } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
      }
    } else {
      std::cerr << "Invalid argv param: " << arg << "\n";
    }
  }
}

int main(int argc, char* argv[]) {
  handleArg(argc, argv);
  LOG("Running in mode: " + toString(mode));
  LOG("Logger has been integrated");
  printInfo();
  runMenu();

  return 0;
}