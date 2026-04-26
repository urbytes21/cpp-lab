// Adapters is a structural design pattern that allows objects with incompatible
// interfaces to collaborate. Appicability:
// (*) When you want to use some existing class, but its interface isn’t
// compatible with the rest of your code
// (**)When you want to reuse several existing subclasses that lack some common
// functionality that can’t be added to the superclass.

// UML: docs/uml/patterns_structural_adapter.drawio.svg

#include <iostream>

namespace adapter_pattern {
/**
 * The Adaptee contains some useful behavior, but its interface is incompatible
 * with the existing client code. The Adaptee needs some adaptation before the
 * client code can use it.
 */
class Adaptee {
 public:
  std::string specificRequest() {
    dummy_++;
    return "Adaptee: The adaptee's behavior.";
  }

 private:
  int dummy_{};
};

/**
 * The Target defines the domain-specific interface used by the client code.
 */
class Target {
 public:
  virtual std::string request() { return "   Target: The target's behavior."; }
};

// ============================================================================================================
// [Q] How can we make the clientCode works with Adaptee without change this
// function (e.g this is in front-end)
// => Create an Adapter
// ============================================================================================================

/**
 * The Adapter makes the Adaptee's interface compatible with the Target's
 * interface.
 */
class Adapter : public Target {
 private:
  Adaptee* adaptee_;

 public:
  explicit Adapter(Adaptee* adaptee) : adaptee_{adaptee} {
    std::cout << "Adapter constructer.\n";
  }

  std::string request() override { return adaptee_->specificRequest(); }
};

/**
 * The client code supports all classes that follow the Target interface.
 */

namespace client {
void clientCode(Target* const target) {
  if (target != nullptr)
    std::cout << "Output: " << target->request() << "\n";
}
}  // namespace client

void run() {
  std::cout << "Client: Can work just fine with the Target objects:\n";
  Target target = Target();
  std::cout << "Target: " << target.request() << "\n";
  client::clientCode(&target);
  std::cout << "\n\n";

  std::cout << "Client: Cannot work with the Adaptee objects:\n";
  Adaptee adaptee = Adaptee();
  std::cout << "Adaptee: " << adaptee.specificRequest() << "\n";
  // Client::clientCode(&adaptee); // error

  std::cout << "Client: But can work with it via the Adapter:\n";
  auto adapter = Adapter(&adaptee);
  client::clientCode(&adapter);
  std::cout << "\n";
}
}  // namespace adapter_pattern

namespace case_study {
// Target interface expected by the existing system
class PaymentSystem {
 public:
  virtual void payWithCard(const std::string& cardNumber) {
    std::cout << "Payment using card: " << cardNumber << "\n";
  }

  virtual ~PaymentSystem() = default;
};

// Adaptee: a new payment API with an incompatible interface
class PayPalAPI {
 public:
  void sendPayment(const std::string& email) {
    std::cout << "Payment sent via PayPal to " << email << "\n";
    dummy_++;
  }

 private:
  int dummy_{};
};

// Adapter: makes PayPalAPI compatible with PaymentSystem
class PayPalAdapter : public PaymentSystem {
 private:
  PayPalAPI paypal_;

 public:
  void payWithCard(const std::string& cardNumber) override {
    // Treat the cardNumber parameter as a PayPal email
    paypal_.sendPayment(cardNumber);
  }
};

// Client code: uses the old interface without modification
void run() {
  std::string method;
  std::string input;
  method = std::string("card") + std::string("");
  input = "1234-5678-9999";
  // method = std::string("paypal") + std::string("");input =
  // "user@example.com";

  std::cout << "Choose payment method (card/paypal): " << method << "\n";

  PaymentSystem* payment_system = nullptr;

  if (method == "card") {
    payment_system = new PaymentSystem();
    payment_system->payWithCard(input);
  } else if (method == "paypal") {
    payment_system = new PayPalAdapter();
    payment_system->payWithCard(input);
  } else {
    std::cout << "Unsupported payment method!\n";
  }

  delete payment_system;
}
}  // namespace case_study

#include "ExampleRegistry.h"

class AdapterExample : public IExample {
 public:
  std::string group() const override { return "dp/structural"; }
  std::string name() const override { return "Adapter"; }
  std::string description() const override { return "Factory Pattern Example"; }
  void execute() override {
    adapter_pattern::run();
    case_study::run();
  }
};

REGISTER_EXAMPLE(AdapterExample, "dp/structural", "Adapter");