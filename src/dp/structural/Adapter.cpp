// Adapters is a structural design pattern that allows objects with incompatible
// interfaces to collaborate. Appicability:
// (*) When you want to use some existing class, but its interface isn’t
// compatible with the rest of your code
// (**)When you want to reuse several existing subclasses that lack some common
// functionality that can’t be added to the superclass.

// UML: docs/uml/patterns_structural_adapter.drawio.svg

#include "Logger.h"

namespace adapter_pattern {
/**
 * The Adaptee contains some useful behavior, but its interface is incompatible
 * with the existing client code. The Adaptee needs some adaptation before the
 * client code can use it.
 */
class Adaptee {
 public:
  void specific_request() {
    dummy_++;
    LOG("executed");
  }

 private:
  int dummy_{};
};

/**
 * The Target defines the domain-specific interface used by the client code.
 */
class Target {
 public:
  virtual void request() { LOG("executed"); }
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
  explicit Adapter(Adaptee* adaptee) : adaptee_{adaptee} { LOG("constructed"); }

  void request() override { return adaptee_->specific_request(); }
};

void run() {
  LOG("Adapter Example");

  // The client code supports all classes that follow the Target interface.
  auto client_code = [](Target* target) {
    LOG("executed");
    target->request();
  };

  LOG("Client: Can work just fine with the Target objects:");
  Target target = Target();
  client_code(&target);

  LOG("Client: Cannot work with the Adaptee objects:");
  Adaptee adaptee = Adaptee();
  // Client::clientCode(&adaptee); // error

  LOG("Client: But can work with it via the Adapter:");
  auto adapter = Adapter(&adaptee);
  client_code(&adapter);
}
}  // namespace adapter_pattern

namespace case_study {
// Target interface expected by the existing system
class PaymentSystem {
 public:
  virtual void pay_with_card(const std::string& card_number) {
    LOG_S("Payment using card: " << card_number);
  }

  virtual ~PaymentSystem() = default;
};

// Adaptee: a new payment API with an incompatible interface
class PayPalAPI {
 public:
  void send_payment(const std::string& email) {
    LOG_S("Payment sent via PayPal to " << email);
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
  void pay_with_card(const std::string& cardNumber) override {
    // Treat the cardNumber parameter as a PayPal email
    paypal_.send_payment(cardNumber);
  }
};

// Client code: uses the old interface without modification
void run() {
  LOG("Case Study Example");
  std::string method;
  std::string input;
  method = std::string("card") + std::string("");
  input = "1234-5678-9999";
  // method = std::string("paypal") + std::string("");input =
  // "user@example.com";

  LOG_S("Choose payment method (card/paypal): " << method);

  PaymentSystem* payment_system = nullptr;

  if (method == "card") {
    payment_system = new PaymentSystem();
    payment_system->pay_with_card(input);
  } else if (method == "paypal") {
    payment_system = new PayPalAdapter();
    payment_system->pay_with_card(input);
  } else {
    LOG("Unsupported payment method!");
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

REGISTER_EXAMPLE(AdapterExample);