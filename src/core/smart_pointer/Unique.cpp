#include <cstring>
#include <memory>
#include "Logger.h"

namespace {
class Resource {
 public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }

  void use() {
    std::cout << "Using resource\n";
    dummy_++;
  }

 private:
  int dummy_{};
};

void run() {
  LOG("unique_ptr example");
  {
    auto p1 = std::make_unique<Resource>();
    p1->use();

    // auto p2 = p1; // compile error -> copy not allow
    auto p2 = std::move(p1);
    std::cout << "p1 is " << (p1 ? "not null" : "null") << "\n";
    p2->use();
  }
  LOG("End scope. RAII");  // automatically deletes the object uinique_ptr owns
}
}  // namespace

#include "ExampleRegistry.h"

class Unique : public IExample {
 public:
  std::string group() const override { return "core/smart_pointer"; }
  std::string name() const override { return "Unique"; }
  std::string description() const override { return "Unique Pointer Example"; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(Unique, "core/smart_pointer", "Unique");