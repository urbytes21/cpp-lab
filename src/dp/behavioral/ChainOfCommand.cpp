// CoR is a behavioral design pattern that lets you pass requests along a chain
// of handlers. Upon receiving a request, each handler decides either to process
// the request or to pass it to the next handler in the chain. Allows an object
// to send a command without knowing what object will receive and handle it.
// Appicability:
// (*) when it’s essential to execute several handlers in a particular order.
// (**)when the set of handlers and their order are supposed to change at
// runtime.

// UML: docs/uml/patterns_behavioral_CoR.drawio.svg

#include <string>
#include "Logger.h"

namespace {
namespace co_r {
/*
 *  Handler - defines an interface for handling requests
 */
class IHandler {
 public:
  virtual ~IHandler() = default;
  virtual void setNextHandler(IHandler* handler) = 0;
  virtual IHandler* setNext(IHandler* handler) = 0;
  virtual void handle(const std::string& request) = 0;
};

class AbstractHandler : public IHandler {
 private:
  IHandler* setNext_{};

 public:
  AbstractHandler() = default;

  void setNextHandler(IHandler* handler) override { this->setNext_ = handler; }

  // handler1->setNext(handler2)->setNext(handler3)
  IHandler* setNext(IHandler* handler) override {
    this->setNext_ = handler;
    return handler;
  }

  void handle(const std::string& request) override {
    if (this->setNext_ != nullptr) {
      this->setNext_->handle(request);
    } else {
      LOG("\tNo handler processed request: " + request);
    }
  }
};

/**
 * CoreteHandlers - handles the requests it is responsible for
 * If it can handle the request it does so, otherwise it sends the request to
 * its successor
 */
class ConcreteHandlerGET : public AbstractHandler {
 private:
  static constexpr const char* kHeader = "GET";

 public:
  void handle(const std::string& request) override {
    if (request.rfind(kHeader, 0) == 0) {
      // If request is eligible, handle it
      LOG("\tHandle GET request: " + request);
      // In realworld, it should be other logics here
    } else {
      AbstractHandler::handle(request);
    }
  }
};

class ConcreteHandlerPUT : public AbstractHandler {
 private:
  static constexpr const char* kHeader = "PUT";

 public:
  void handle(const std::string& request) override {
    if (request.rfind(kHeader, 0) == 0) {
      LOG("\tHandle PUT request: " + request);
    } else {
      AbstractHandler::handle(request);
    }
  }
};

class ConcreteHandlerPOST : public AbstractHandler {
 private:
  static constexpr const char* kHeader = "POST";

 public:
  void handle(const std::string& request) override {
    if (request.rfind(kHeader, 0) == 0) {
      LOG("\tHandle POST request: " + request);
    } else {
      AbstractHandler::handle(request);
    }
  }
};

/**
 * Client - sends commands to the first object in the chain that may handle the
 * command
 */
namespace client {
void clientCode(IHandler& handler, const std::string& request) {
  handler.handle(request);
}
}  // namespace client

void run() {
  // Setup Chain of Responsibility
  IHandler* post_handler = new ConcreteHandlerPOST();
  IHandler* gett_handler = new ConcreteHandlerGET();
  IHandler* putt_handler = new ConcreteHandlerPUT();
  post_handler->setNext(gett_handler)->setNext(putt_handler);

  // Send requests to the chain
  std::string dummy = "DUMMY ..";
  std::string post_request = "POST /test/demo_form.php HTTP/1.1 ..";
  std::string get_request = "GET /users/123 ..";
  LOG("Send dummy request");
  client::clientCode(*post_handler, dummy);
  LOG("Send POST request");
  client::clientCode(*post_handler, post_request);
  LOG("Send GET request");
  client::clientCode(*post_handler, get_request);

  delete post_handler;
  delete gett_handler;
  delete putt_handler;
}
}  // namespace co_r

}  // namespace

#include "ExampleRegistry.h"

class ChainOfResponsibilityExample : public IExample {
 public:
  std::string group() const override { return "dp/behavioral"; }
  std::string name() const override { return "ChainOfResponsibility"; }
  std::string description() const override { return "CoR Pattern Example"; }
  void execute() override { co_r::run(); }
};

REGISTER_EXAMPLE(ChainOfResponsibilityExample, "dp/behavioral",
                 "ChainOfResponsibility");