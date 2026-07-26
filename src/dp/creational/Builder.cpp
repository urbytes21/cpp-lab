// cppcheck-suppress-file [functionStatic]

#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include "Logger.h"

#include "ExampleRegistry.h"

namespace {
namespace builder_pattern {
class Product {
 private:
  std::vector<std::string> parts_;

 public:
  void add_part(const std::string& part) { parts_.push_back(part); }

  void print() const {
    LOG("Product parts: ");
    std::ostringstream oss;
    for (size_t i = 0; i < parts_.size(); ++i) {
      oss << parts_[i];
      if (i + 1 < parts_.size()) {
        oss << ", ";
      }
    }
    LOG(oss.str());
  }
};

/// @class Builder Interface
/// @brief specifics methods for creating the different parts
class IBuilder {
 public:
  virtual ~IBuilder() = default;
  virtual IBuilder& reset() = 0;
  virtual IBuilder& produce_part_1() = 0;
  virtual IBuilder& produce_part_2() = 0;
  virtual IBuilder& produce_part_3() = 0;

  virtual std::unique_ptr<Product> build() = 0;
};

class AbstractBuilder : public IBuilder {
 protected:
  std::unique_ptr<Product> product_;

 public:
  explicit AbstractBuilder() : product_{std::make_unique<Product>()} {}

  AbstractBuilder(const AbstractBuilder&) = delete;
  AbstractBuilder& operator=(const AbstractBuilder&) = delete;

  AbstractBuilder(AbstractBuilder&&) = default;
  AbstractBuilder& operator=(AbstractBuilder&&) = default;

  /// @brief the child classes are no longer override this function
  IBuilder& reset() final {
    product_ = std::make_unique<Product>();
    return *this;
  }
};

/// @class Concrete Builder
class SimpleBuilder : public AbstractBuilder {
 public:
  IBuilder& produce_part_1() override {
    product_->add_part("PART1");
    return *this;
  }

  IBuilder& produce_part_2() override {
    product_->add_part("PART2");
    return *this;
  }

  IBuilder& produce_part_3() override {
    product_->add_part("PART3");
    return *this;
  }

  std::unique_ptr<Product> build() override { return std::move(product_); }
};

class ComplexBuilder : public AbstractBuilder {
 public:
  IBuilder& produce_part_1() override {
    product_->add_part("PART_1-X9a7Fq!2@Lm#48Z");
    return *this;
  }

  IBuilder& produce_part_2() override {
    product_->add_part("PART_2-X9a7Fq!2@Lm#48Z");
    return *this;
  }

  IBuilder& produce_part_3() override {
    product_->add_part("PART_3-X9a7Fq!2@Lm#48Z");
    return *this;
  }

  std::unique_ptr<Product> build() override { return std::move(product_); }
};

void run() {
  auto client_code = [](IBuilder* const builder) {
    // product 1
    auto p1 =
        (*builder).produce_part_1().produce_part_2().produce_part_3().build();
    p1->print();

    // product 2
    auto p2 = (*builder).reset().produce_part_1().build();
    p2->print();
  };

  {
    LOG("ConcreteBuilder: Simple");
    auto builder = std::make_unique<SimpleBuilder>();
    client_code(builder.get());
  }
  {
    LOG("ConcreteBuilder: Complex");
    IBuilder* builder = new ComplexBuilder();
    client_code(builder);
    delete builder;
  }
}
}  // namespace builder_pattern
}  // namespace

class BuilderExample : public IExample {
 public:
  std::string group() const override { return "dp/creational"; }
  std::string name() const override { return "Builder"; }
  std::string description() const override { return "Builder Pattern Example"; }
  void execute() override { builder_pattern::run(); }
};

REGISTER_EXAMPLE(BuilderExample);