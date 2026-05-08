// cppcheck-suppress-file [knownConditionTrueFalse]

#include <exception>
#include <optional>
#include <stdexcept>
#include <string>
#include "ExampleRegistry.h"
#include "Logger.h"

namespace {

int global = 21;

/**
 * @brief ambiguous issue
 * 
 * @param condition 
 * @return int 
 */
int bad_api_status(bool condition) {
  return condition ? global : -1;
}

int bad_api_throw(bool condition) {
  if (!condition) {
    throw std::runtime_error("required value does not exist.");
  }

  return 0;
}

int* bad_api_ptr(bool condition) {
  return condition ? &global : nullptr;
}

std::optional<int> optional_api(bool condition) {
  if (!condition) {
    return std::nullopt;
  }
  return global;
}

void run() {
  LOG("=== std::optional Example ===");

  bool condition = false;

  // Bad patterns
  {
    LOG("API (ambiguous):");
    auto value = bad_api_status(condition);
    LOG("value = " + std::to_string(value));

    LOG("API (pointer):");
    if (const auto* ptr = bad_api_ptr(condition)) {
      LOG("value = " + std::to_string(*ptr));
    } else {
      LOG("null pointer");
    }
  }

  {
    LOG("API (thow):");
    try {
      auto value = bad_api_throw(condition);
      LOG("value = " + std::to_string(value));
    } catch (const std::exception& e) {
      LOG(std::string("exception: ") + e.what());
    }
  }
  
  // Good pattern
  LOG("API (optional):");
  auto opt = optional_api(condition);

  // 1. Check explicitly
  if (opt) {
    LOG("value = " + std::to_string(*opt));  // preferred over value()
  } else {
    LOG("empty");
  }

  // 2. Provide default
  int v = opt.value_or(-1);
  LOG("value_or(-1) = " + std::to_string(v));

  // 3. Early return style (clean pattern)
  auto process = [](std::optional<int> v) {
    if (!v) {
      LOG("no value, exit early");
      return;
    }
    LOG("processing value = " + std::to_string(*v));
  };
  process(opt);

  // 4. Dangerous usage
  try {
    LOG("Trying value()...");
    int x = opt.value();  // throws if empty
    LOG("value = " + std::to_string(x));
  } catch (const std::exception& e) {
    LOG(std::string("exception: ") + e.what());
  }
}

}  // namespace

class Optional : public IExample {
 public:
  std::string group() const override { return "core/utils"; }
  std::string name() const override { return "std::optional"; }
  std::string description() const override {
    return "The examples for <optional>";
  }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(Optional);