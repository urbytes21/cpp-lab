// cppcheck-suppress-file [functionStatic]

// Builder is a creational design pattern that lets you construct complex
// objects step by step. The pattern allows you to produce different types and
// representations of an object using the same construction code. Appicability:
// (*)  Use the Builder pattern to get rid of a “telescoping constructor”.
// (**) when you want your code to be able to create different representations
// of some product (for example, stone and wooden houses).

// UML: docs/uml/patterns_behavioral_iterator.drawio.svg

#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include "Logger.h"

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

/**
 * The Builder interface specifies methods for creating the different parts of
 * the Product objects.
 */
class IBuilder {
 public:
  virtual ~IBuilder() = default;
  virtual IBuilder& reset() = 0;
  virtual IBuilder& produce_part_1() = 0;
  virtual IBuilder& produce_part_2() = 0;
  virtual IBuilder& produce_part_3() = 0;

  virtual Product* build() = 0;
};

class AbstractBuilder : public IBuilder {
 protected:
  Product* product_;

 public:
  explicit AbstractBuilder() { product_ = new Product(); }

  ~AbstractBuilder() override { delete product_; }

  AbstractBuilder(const AbstractBuilder& other) {

    delete product_;

    product_ = new Product();
    *product_ = *other.product_;
  }

  AbstractBuilder& operator=(const AbstractBuilder& other) {
    if (this == &other) {
      return *this;
    }

    delete product_;
    product_ = new Product();
    *product_ = *other.product_;

    return *this;
  }

  // the child classes are no longer override this function
  IBuilder& reset() final {

    delete product_;
    product_ = new Product();

    return *this;
  }
};

/**
 * The Concrete Builder classes follow the Builder interface and provide
 * specific implementations of the building steps. Your program may have several
 * variations of Builders, implemented differently.
 */
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

  Product* build() override { return product_; }
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

  Product* build() override { return product_; }
};

void run() {
  auto client_code = [](IBuilder* const builder) {
    const Product* p1 =
        (*builder).produce_part_1().produce_part_2().produce_part_3().build();
    p1->print();
    const Product* p2 = (*builder).reset().produce_part_1().build();
    p2->print();
  };

  {
    LOG("ConcreteBuilder: Simple");
    IBuilder* builder = new SimpleBuilder();
    client_code(builder);
    delete builder;
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

#include "ExampleRegistry.h"

class BuilderExample : public IExample {
 public:
  std::string group() const override { return "dp/creational"; }
  std::string name() const override { return "Builder"; }
  std::string description() const override { return "Builder Pattern Example"; }
  void execute() override { builder_pattern::run(); }
};

REGISTER_EXAMPLE(BuilderExample);