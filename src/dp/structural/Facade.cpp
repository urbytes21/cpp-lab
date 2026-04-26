// cppcheck-suppress-file [functionStatic]

// Facade is a structural design pattern that provides a simplified interface
// to a library, a framework, or any other complex set of classes.
// Appicability:
// (*)   when you need to have a limited but straightforward interface to a
// complex subsystem.
// (**)  when you want to structure a subsystem into layers.
// UML: docs/uml/patterns_structural_facade.drawio.svg

#include <iostream>
namespace {
namespace problem {

class AuthSubSystem {
 public:
  virtual ~AuthSubSystem() = default;
  void login() {
    std::cout << "AuthSubSystem: login\n";
    dummy_++;
  }

 private:
  int dummy_{};
};

class ValidatorSubSystem {
 public:
  virtual ~ValidatorSubSystem() = default;
  virtual void check() {
    std::cout << "ValidatorSubSystem: check input\n";
    dummy_++;
  }

 private:
  int dummy_{};
};

class LoggerSubSystem {
 public:
  virtual ~LoggerSubSystem() = default;
  void write() {
    std::cout << "LoggerSubSystem: write log\n";
    dummy_++;
  }

 private:
  int dummy_{};
};

class BackendSubSystem {
 public:
  virtual ~BackendSubSystem() = default;
  void send() {
    std::cout << "BackendSubSystem: send request\n";
    dummy_++;
  }

 private:
  int dummy_{};
};

namespace client1 {
// The client must manually interact with each subsystem.
// This creates unnecessary complexity.
void clientCode(ValidatorSubSystem& s1, AuthSubSystem& s2, LoggerSubSystem& s3,
                BackendSubSystem& s4) {
  s1.check();
  s2.login();
  s3.write();
  s4.send();

  // In real code, the client must also
  //   - know call ordering
  //   - combine subsystem operations
  //   - manage lifecycle and error handling
}
}  // namespace client1

namespace client2 {
// The client must manually interact with each subsystem.
// This creates unnecessary complexity.
void clientCode(ValidatorSubSystem& s1) {
  s1.check();
}
}  // namespace client2

void run() {
  std::cout << "\n\nProblem\n";

  ValidatorSubSystem v;
  AuthSubSystem a;
  LoggerSubSystem l;
  BackendSubSystem b;

  client1::clientCode(v, a, l, b);
  client2::clientCode(v);
}
}  // namespace problem

namespace facade {

class AuthSubSystem {
 public:
  virtual ~AuthSubSystem() = default;
  void login() {
    std::cout << "AuthSubSystem: login\n";
    dummy_++;
  }

 private:
  int dummy_{};
};

class ValidatorSubSystem {
 public:
  virtual ~ValidatorSubSystem() = default;
  void check() {
    std::cout << "ValidatorSubSystem: check input\n";
    dummy_++;
  }

 private:
  int dummy_{};
};

class LoggerSubSystem {
 public:
  virtual ~LoggerSubSystem() = default;
  void write() {
    std::cout << "LoggerSubSystem: write log\n";
    dummy_++;
  }

 private:
  int dummy_{};
};

class BackendSubSystem {
 public:
  virtual ~BackendSubSystem() = default;
  virtual void send() const { std::cout << "BackendSubSystem: send request\n"; }
};

// =======================
// Mock subclasses (for testing)
// =======================
class MockBackendSubSystem : public BackendSubSystem {
 public:
  void send() const override { std::cout << "[MockBackend] fake-send\n"; }
};

/**
 * The Facade class provides a simple interface to the complex logic of one or
 * several subsystems. The Facade delegates the client requests to the
 * appropriate objects within the subsystem. The Facade is also responsible for
 * managing their lifecycle. All of this shields the client from the undesired
 * complexity of the subsystem.
 */
class RequestFacade {
 protected:
  AuthSubSystem* auth_;
  ValidatorSubSystem* validator_;
  LoggerSubSystem* logger_;
  BackendSubSystem* backend_;

  /**
   * Depending on your application's needs, you can provide the Facade with
   * existing subsystem objects or force the Facade to create them on its own.
   */
 public:
  /**
   * In this case we will delegate the memory ownership to Facade Class
   */
  explicit RequestFacade(AuthSubSystem* s1 = nullptr,
                         ValidatorSubSystem* s2 = nullptr,
                         LoggerSubSystem* s3 = nullptr,
                         BackendSubSystem* s4 = nullptr) {
    this->auth_ = s1 ? s1 : new AuthSubSystem();
    this->validator_ = s2 ? s2 : new ValidatorSubSystem();
    this->logger_ = s3 ? s3 : new LoggerSubSystem();
    this->backend_ = s4 ? s4 : new BackendSubSystem();
  }

  ~RequestFacade() {
    delete auth_;
    delete validator_;
    delete logger_;
    delete backend_;
  }

  /**
   * The Facade's methods are convenient shortcuts to the sophisticated
   * functionality of the subsystems. However, clients get only to a fraction of
   * a subsystem's capabilities.
   */
  void sendRequest() {
    validator_->check();
    auth_->login();
    logger_->write();
    backend_->send();
  }

  void validate() { validator_->check(); }
};

namespace client1 {
/**
 * The client code works with complex subsystems through a simple interface
 * provided by the Facade. When a facade manages the lifecycle of the subsystem,
 * the client might not even know about the existence of the subsystem. This
 * approach lets you keep the complexity under control.
 */
void clientCode(RequestFacade& facade) {
  facade.sendRequest();
}
}  // namespace client1

namespace client2 {
/**
 * The client code works with complex subsystems through a simple interface
 * provided by the Facade. When a facade manages the lifecycle of the subsystem,
 * the client might not even know about the existence of the subsystem. This
 * approach lets you keep the complexity under control.
 */
void clientCode(RequestFacade& facade) {
  facade.validate();
}
}  // namespace client2

void run() {
  std::cout << "\n\nFacade\n";
  {
    auto* facade = new RequestFacade();
    client1::clientCode(*facade);
    client2::clientCode(*facade);
    delete facade;
  }

  {
    // injected subsystems for mocktest
    std::cout << "\n";
    auto* b = new MockBackendSubSystem();
    auto* facade = new RequestFacade(nullptr, nullptr, nullptr, b);
    client1::clientCode(*facade);
    delete facade;
  }
}
}  // namespace facade
}  // namespace

#include "ExampleRegistry.h"

class FacadeExample : public IExample {
 public:
  std::string group() const override { return "dp/structural"; }
  std::string name() const override { return "Facade"; }
  std::string description() const override { return "Facade Pattern Example"; }
  void execute() override {
    problem::run();
    facade::run();
  }
};

REGISTER_EXAMPLE(FacadeExample, "dp/structural", "Facade");