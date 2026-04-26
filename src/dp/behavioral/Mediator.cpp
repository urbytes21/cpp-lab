// Mediator is a behavioral design pattern that lets you reduce chaotic
// dependencies between objects. The pattern restricts direct communications
// between the objects and forces them to collaborate only via a mediator
// object. Usage examples: The most popular usage of the Mediator pattern in C++
// code is facilitating communications between GUI components of an app. The
// synonym of the Mediator is the `Controller` part of MVC pattern.
// Appicability:
// (*)   when your collection has a complex data structure under the hood, but
// you want to hide its complexity from clients (either for convenience or
// security reasons).
// (**)  when you can’t reuse a component in a different program because it’s
// too dependent on other components.
// (***) when you find yourself creating tons of component subclasses just to
// reuse some basic behavior in various contexts.

// UML: docs/uml/patterns_behavioral_mediator.drawio.svg

#include <iostream>
#include <string>
#include <utility>
#include <vector>
namespace {
namespace mediator {

enum class Event {
  kCreate = 0,
  kRead,
  kUpdate,
  kDelete,
};

inline const char* getEventName(const Event& e) {
  switch (e) {
    case Event::kCreate:
      return "CREATE";
    case Event::kRead:
      return "READ";
    case Event::kUpdate:
      return "UPDATE";
    case Event::kDelete:
      return "DELETE";
  }
  return "invalid_event";
}

class IComponent {
 public:
  virtual ~IComponent() = default;

  virtual void send(const Event& e) = 0;
  virtual void receive(const Event& e) = 0;
};

/**
 * The Mediator interface declares methods of communication with components,
 * which usually include just a single notification method. Components may pass
 * any context as arguments of this method, including their own objects, but
 * only in such a way that no coupling occurs between a receiving component and
 * the sender’s class.
 */
class IMediator {
 public:
  virtual ~IMediator() = default;
  virtual void registerComponent(IComponent* const& c) = 0;
  virtual void notify(IComponent* sender, const Event& e) = 0;
};

/**
 * Concrete Mediators implement cooperative behavior by coordinating several
 * components. Concrete mediators often keep references to all components they
 * manage and sometimes even manage their lifecycle.
 */
class ComponentMediator : public IMediator {
 private:
  std::vector<IComponent*> components_;

 public:
  void registerComponent(IComponent* const& c) override {
    components_.push_back(c);
  }

  void notify(IComponent* const sender, const Event& e) override {
    for (auto* c : components_) {
      if (c != sender) {
        c->receive(e);
      }
    }
  }
};

/**
 * Components are various classes that contain some business logic.
 * Each component has a reference to a mediator, declared with the type of the
 * mediator interface. The component isn’t aware of the actual class of the
 * mediator, so you can reuse the component in other programs by linking it to a
 * different mediator.
 */
class AbstractComponent : public IComponent {
 private:
  const std::string id_;

 protected:
  IMediator* mediator_;
  void log(const Event& e, const std::string& msg) const {
    std::cout << "\t" + msg + "-id:" + id_ + "-event:" + getEventName(e) + "\n";
  }

 public:
  explicit AbstractComponent(std::string  id,
                             IMediator* const m = nullptr)
      : id_{std::move(id)}, mediator_{m} {};
};

/**
 * Concrete Components implement various functionality. They don't depend on
 * other components. They also don't depend on any concrete mediator classes.
 */
class ConreteComponent : public AbstractComponent {
 public:
  explicit ConreteComponent(const std::string& id, IMediator* const m = nullptr)
      : AbstractComponent{id, m} {}

  void send(const Event& e) override {
    log(e, "[SEND]");
    if (mediator_ != nullptr)
      mediator_->notify(this, e);
  }

  void receive(const Event& e) override {
    log(e, "[RECV]");
    // Additional handling logic can go here
  }
};

namespace client {
void clientCode(IComponent* comp) {
  comp->send(Event::kRead);
}
}  // namespace client

void run() {
  IMediator* mediator = new ComponentMediator();
  IComponent* c1 = new ConreteComponent("1763700876", mediator);
  IComponent* c2 = new ConreteComponent("1763700882", mediator);
  IComponent* c3 = new ConreteComponent("1763700899", mediator);
  IComponent* c4 = new ConreteComponent("1763700900", mediator);

  // Only c1, c3, c4 receive notifications.
  mediator->registerComponent(c1);
  mediator->registerComponent(c3);
  mediator->registerComponent(c4);

  // c2 triggers event => observed by others
  client::clientCode(c2);

  delete mediator;
  delete c1;
  delete c2;
  delete c3;
  delete c4;
}
}  // namespace mediator
}  // namespace

#include "ExampleRegistry.h"

class MediatorExample : public IExample {
 public:
  std::string group() const override { return "dp/behavioral"; }
  std::string name() const override { return "Mediator"; }
  std::string description() const override {
    return "Mediator Pattern Example";
  }
  void execute() override { mediator::run(); }
};

REGISTER_EXAMPLE(MediatorExample, "dp/behavioral", "Mediator");