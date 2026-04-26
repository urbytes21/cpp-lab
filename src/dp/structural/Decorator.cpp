// Decorator is a structural design pattern that lets you attach new behaviors
// to objects by placing these objects inside special wrapper objects that
// contain the behaviors. Appicability:
// (*)   when you need to be able to assign extra behaviors to objects at
// runtime without breaking the code that uses these objects.
// (**)  when it’s awkward or not possible to extend an object’s behavior using
// inheritance. UML: docs/uml/patterns_structural_decorator.drawio.svg

#include <iostream>
#include <string>

namespace {
namespace problem {

class IComponent {
 public:
  virtual ~IComponent() = default;
  virtual std::string operation() const = 0;
};

class ConcreteComponent : public IComponent {
 public:
  std::string operation() const override { return "ConcreteComponent"; }
};

class ComponentWithA : public ConcreteComponent {
 public:
  std::string operation() const override {
    return ConcreteComponent::operation() + " + FeatureA";
  }
};

class ComponentWithB : public ConcreteComponent {
 public:
  std::string operation() const override {
    return ConcreteComponent::operation() + " + FeatureB";
  }
};

class ComponentWithAandB : public ConcreteComponent {
 public:
  std::string operation() const override {
    return ConcreteComponent::operation() + " + FeatureA + FeatureB";
  }
};

// [P1]
// If you have 3 features , e.g FeatureC -> many combinations
// If you have 5 features -> 32 subclasses

namespace client {
void clientCode(const IComponent& comp) {
  std::cout << comp.operation() << "\n";
}
}  // namespace client

void run() {
  std::cout << "\n\nProblem\n";
  IComponent* simple = new ConcreteComponent;
  client::clientCode(*simple);

  IComponent* with_a = new ComponentWithA;
  client::clientCode(*with_a);

  IComponent* with_b = new ComponentWithB;
  client::clientCode(*with_b);

  IComponent* with_ab = new ComponentWithAandB;
  client::clientCode(*with_ab);

  delete simple;
  delete with_a;
  delete with_b;
  delete with_ab;
}

}  // namespace problem

namespace decorator_pattern {
class IComponent {
 public:
  virtual ~IComponent() = default;
  virtual std::string operation() const = 0;
};

/**
 * Concrete Component
 * - is a class of objects being wrapped.
 * - defines the basic behavior, which can be altered by decorators.
 */
class ConcreteComponent : public IComponent {
 public:
  std::string operation() const override { return "ConcreteComponent"; }
};

/**
 * The base Decorator class follows the same interface as the other components.
 * - has a field for referencing a wrapped object.
 * - the field’s type should be declared as the component interface so it can
 * contain both concrete components and decorators.
 * - the base decorator delegates all operations to the wrapped object.
 */
class BaseDecorator : public IComponent {
 protected:
  IComponent* component_;

 public:
  explicit BaseDecorator(IComponent* component) : component_{component} {}

  /**
   * The Decorator delegates all work to the wrapped component.
   */
  std::string operation() const override { return component_->operation(); }
};

/**
 * Concrete Decorators :
 * - call the wrapped object and alter its result in some way.
 * - define extra behaviors that can be added to components dynamically.
 * - override methods of the base decorator and execute their behavior either
 * before or after calling the parent method.
 */
class ConcreteDecoratorA : public BaseDecorator {
 public:
  explicit ConcreteDecoratorA(IComponent* component)
      : BaseDecorator{component} {}

  std::string operation() const override {
    return BaseDecorator::operation() + " + FeatureA";
  }
};

class ConcreteDecoratorB : public BaseDecorator {
 public:
  explicit ConcreteDecoratorB(IComponent* component)
      : BaseDecorator{component} {}

  std::string operation() const override {
    return BaseDecorator::operation() + " + FeatureB";
  }
};

class ConcreteDecoratorC : public BaseDecorator {
 public:
  explicit ConcreteDecoratorC(IComponent* component)
      : BaseDecorator{component} {}

  std::string operation() const override {
    return BaseDecorator::operation() + " + FeatureC";
  }
};

namespace client {
void clientCode(const IComponent& comp) {
  std::cout << comp.operation() << "\n";
}
}  // namespace client

void run() {
  std::cout << "\n\nDecorator\n";
  IComponent* simple = new ConcreteComponent;
  client::clientCode(*simple);

  IComponent* with_a = new ConcreteDecoratorA(simple);
  client::clientCode(*with_a);

  IComponent* with_b = new ConcreteDecoratorB(simple);
  client::clientCode(*with_b);

  IComponent* with_ab = new ConcreteDecoratorB(with_a);
  client::clientCode(*with_ab);

  IComponent* with_abc = new ConcreteDecoratorC(with_ab);
  client::clientCode(*with_abc);

  delete simple;
  delete with_a;
  delete with_b;
  delete with_ab;
  delete with_abc;
}
}  // namespace decorator_pattern

}  // namespace

#include "ExampleRegistry.h"

class DecoratorExample : public IExample {
 public:
  std::string group() const override { return "dp/structural"; }
  std::string name() const override { return "Decorator"; }
  std::string description() const override {
    return "Decorator Pattern Example";
  }
  void execute() override {
    problem::run();
    decorator_pattern::run();
  }
};

REGISTER_EXAMPLE(DecoratorExample, "dp/structural", "Decorator");