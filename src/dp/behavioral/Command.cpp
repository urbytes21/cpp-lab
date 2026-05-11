// Command is a behavioral design pattern that turns a request into a
// stand-alone object that contains all information about the request.
// (receivers, payloads) This transformation lets you pass requests as a method
// arguments, delay or queue a request’s execution, and support undoable
// operations. Allows an object to send a command without knowing what object
// will receive and handle it. Appicability:
// (*)   when you want to parameterize objects with operations.
// (**)  when you want to queue operations, schedule their execution, or execute
// them remotely.
// (***) when you want to implement reversible operations.

// UML: docs/uml/patterns_behavioral_command.drawio.svg

#include <string>
#include <utility>
#include "Logger.h"

namespace {
namespace command {

/**
 * The Command interface usually declares just a single method for executing the
 * command. e.g. Save, Undo, Jump, Backup, CreateOrder
 */
class ICommand {
 public:
  virtual ~ICommand() = default;
  virtual void execute() const = 0;
};

/**
 * The Receiver class contains some business logic. Almost any object may act as
 * a receiver. Most commands only handle the details of how a request is passed
 * to the receiver, while the receiver itself does the actual work. e.g.
 * Document, GameCharacter, DB service
 */
class Receiver {
 public:
  void doCheck() {
    LOG("Receiver checking... ");
    dummy_++;
  };

  void doInit() {
    LOG("Receiver initializing... ");
    dummy_++;
  };

  void doLaunch(const std::string& arg) {
    LOG("Receiver launching...  \n\t" + arg);
    dummy_++;
  };

 private:
  int dummy_{};
};

/**
 * Concrete Commands implement various kinds of requests.
 *  A concrete command isn’t supposed to perform the work on its own, but rather
 * to pass the call to one of the business logic objects. However, for the sake
 * of simplifying the code, these classes can be merged.
 */
class SimpleConcreteCommand : public ICommand {
 public:
  void execute() const override { LOG("executed"); }
};

class ComplexConcreteCommand : public ICommand {
 private:
  Receiver* receiver_;
  std::string payload_;

 public:
  ComplexConcreteCommand(Receiver* receiver, std::string payload)
      : receiver_{receiver}, payload_{std::move(payload)} {};

  void execute() const override {
    LOG("executed");
    this->receiver_->doCheck();
    this->receiver_->doInit();
    this->receiver_->doLaunch(payload_);
  }
};

/**
 *The Sender class (aka invoker) is responsible for initiating requests.
 *This class must have a field for storing a reference to a command object.
 *The sender triggers that command instead of sending the request directly to
 * the receiver. Note that the sender isn’t responsible for creating the command
 * object. Usually, it gets a pre-created command from the client via the
 * constructor. e.g. Button, Shortcut, Scheduler, Event bus...
 */
class Invoker {
 private:
  ICommand* on_start_;
  ICommand* on_finish_;

 public:
  explicit Invoker(ICommand* s = nullptr) : on_start_{s}, on_finish_{s} {}

  ~Invoker() {
    delete on_start_;
    delete on_finish_;
  }

  void setOnStart(ICommand* command) { this->on_start_ = command; }

  void setOnFinish(ICommand* command) { this->on_finish_ = command; }

  void invoke() const {
    LOG("executed");
    if (on_start_ != nullptr) {
      on_start_->execute();
    }

    if (on_finish_ != nullptr) {
      on_finish_->execute();
    }
  }
};

void run() {
  auto client_code = [](const Invoker* invoker) {
    invoker->invoke();
  };

  // Receiver: UI
  auto* ui = new Receiver();

  // How to execute these command when something triggered
  auto* invoker = new Invoker();
  invoker->setOnStart(new SimpleConcreteCommand());
  invoker->setOnFinish(new ComplexConcreteCommand(ui, "cmd --version"));

  client_code(invoker);
  delete ui;
}
}  // namespace command
}  // namespace

#include "ExampleRegistry.h"

class CommandExample : public IExample {
 public:
  std::string group() const override { return "dp/behavioral"; }
  std::string name() const override { return "Command"; }
  std::string description() const override { return "Command Pattern Example"; }
  void execute() override { command::run(); }
};

REGISTER_EXAMPLE(CommandExample);