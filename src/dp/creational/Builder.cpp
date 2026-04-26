// cppcheck-suppress-file [functionStatic]

// Builder is a creational design pattern that lets you construct complex
// objects step by step. The pattern allows you to produce different types and
// representations of an object using the same construction code. Appicability:
// (*)  Use the Builder pattern to get rid of a “telescoping constructor”.
// (**) when you want your code to be able to create different representations
// of some product (for example, stone and wooden houses).

// UML: docs/uml/patterns_behavioral_iterator.drawio.svg

#include <iostream>
#include <string>
#include <vector>

namespace {
namespace builder_pattern {
class Product {
 private:
  std::vector<std::string> parts_;

 public:
  void addPart(const std::string& part) { parts_.push_back(part); }

  void print() const {
    std::cout << "Product parts: ";
    for (size_t i = 0; i < parts_.size(); ++i) {
      std::cout << parts_[i];
      if (i + 1 < parts_.size())
        std::cout << ", ";
    }
    std::cout << "\n\n";
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
  virtual IBuilder& producePart1() = 0;
  virtual IBuilder& producePart2() = 0;
  virtual IBuilder& producePart3() = 0;

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
  IBuilder& producePart1() override {
    product_->addPart("PART1");
    return *this;
  }

  IBuilder& producePart2() override {
    product_->addPart("PART2");
    return *this;
  }

  IBuilder& producePart3() override {
    product_->addPart("PART3");
    return *this;
  }

  Product* build() override { return product_; }
};

class ComplexBuilder : public AbstractBuilder {
 public:
  IBuilder& producePart1() override {
    product_->addPart("PART_1-X9a7Fq!2@Lm#48Z");
    return *this;
  }

  IBuilder& producePart2() override {
    product_->addPart("PART_2-X9a7Fq!2@Lm#48Z");
    return *this;
  }

  IBuilder& producePart3() override {
    product_->addPart("PART_3-X9a7Fq!2@Lm#48Z");
    return *this;
  }

  Product* build() override { return product_; }
};

namespace client {
void clientCode(IBuilder* const builder) {
  const Product* product1 =
      (*builder).producePart1().producePart2().producePart3().build();
  product1->print();

  const Product* product2 = (*builder).reset().producePart1().build();
  product2->print();
}
}  // namespace Client

void run() {
  {
    std::cout << "ConcreteBuilder: Simple\n";
    IBuilder* builder = new SimpleBuilder();
    client::clientCode(builder);
    delete builder;
  }
  {
    std::cout << "ConcreteBuilder: Complex\n";
    IBuilder* builder = new ComplexBuilder();
    client::clientCode(builder);
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

REGISTER_EXAMPLE(BuilderExample, "dp/creational", "Builder");