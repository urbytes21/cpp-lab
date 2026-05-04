// Observer is a behavioral design pattern that lets you define a subscription
// mechanism to notify multiple objects about any events that happen to the
// object they’re observing. Usage examples: The most popular usage of the
// Observer pattern in C++ code is facilitating communications between GUI
// components of an app. The synonym of the Observer is the `Controller` part of
// MVC pattern. Appicability:
// (*)   when changes to the state of one object may require changing other
// objects, and the actual set of objects is unknown beforehand or changes
// dynamically.
// (**)   when some objects in your app must observe others, but only for a
// limited time or in specific cases.

// UML: docs/uml/patterns_behavioral_observer.drawio.svg

#include <iostream>
#include <list>
#include <string>

namespace {
namespace observer {

enum class Event {
  kCreate = 0,
  kRead,
  kUpdate,
  kDelete,
};

inline const char* getEventName(
    const Event&
        e) {  // 'getEventName' is a static definition in anonymous namespace
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

/**
 * IObserver aka Subscriber
 * The Subscriber interface declares the notification interface.
 * In most cases, it consists of a single update method.
 * The method may have several parameters that let the publisher pass some event
 * details along with the update. E.g. Event Listen to UI events
 */
class IListenerObserver {
 public:
  virtual ~IListenerObserver() = default;

  // update
  virtual void update(const Event& e) = 0;
};

/**
 * Subject aka Publisher
 * The Publisher issues events of interest to other objects.
 * These events occur when the publisher changes its state or executes some
 * behaviors. Publishers contain a subscription infrastructure that lets new
 * subscribers join and current subscribers leave the list.
 *
 * E.g Widget dispatches click events to observers
 */
class IWidgetSubject {
 public:
  virtual ~IWidgetSubject() = default;
  // addListener
  virtual void attach(IListenerObserver* observer) = 0;
  // removeLister
  virtual void detach(IListenerObserver* observer) = 0;
  // e.g.click
  virtual void notify(const Event& e) = 0;
};

class ButtonConcreteSubject : public IWidgetSubject {
 private:
  std::list<IListenerObserver*> listeners_;

 public:
  void attach(IListenerObserver* observer) override {
    listeners_.push_back(observer);
  }

  void detach(IListenerObserver* observer) override {
    listeners_.remove(observer);
  }

  void notify(const Event& e) override {
    std::cout << "[Subject] notify event-" << getEventName(e) << "\n";
    for (IListenerObserver* o : listeners_) {
      o->update(e);
    }
  }
};

class AbstractListenerObserver : public IListenerObserver {
 private:
  int nu_;
  inline static int nuobservers_ = 0;

 protected:
  void log(const Event& e) const {
    std::cout << "\t-id:" << nu_ << "-event:" << getEventName(e) << "\n";
  }

 public:
  explicit AbstractListenerObserver() { nu_ = ++nuobservers_; }
};

/**
 * Concrete Subscribers perform some actions in response to notifications issued
 * by the publisher. All of these classes must implement the same interface so
 * the publisher isn’t coupled to concrete classes.
 */
class ConcreteListenerObserverA : public AbstractListenerObserver {
 private:
  static const inline char* type_ = "A-type";

 public:
  void update(const Event& e) override {
    std::cout << "\tListener: " << type_;
    log(e);
  }
};

class ConcreteListenerObserverB : public AbstractListenerObserver {
 private:
  static const inline char* type_ = "B-type";

 public:
  void update(const Event& e) override {
    std::cout << "\tListener: " << type_;
    log(e);
  }
};

/**
 * The Client creates publisher and subscriber objects separately
 * and then registers subscribers for publisher updates.
 */
namespace client {
void clientCode(IWidgetSubject* const s) {
  s->notify(Event::kUpdate);
}
}  // namespace client

void run() {
  IWidgetSubject* btn = new ButtonConcreteSubject();

  IListenerObserver* listener_1 = new ConcreteListenerObserverA();
  IListenerObserver* listener_2 = new ConcreteListenerObserverA();
  IListenerObserver* listener_3 = new ConcreteListenerObserverA();
  IListenerObserver* listener_4 = new ConcreteListenerObserverB();

  btn->attach(listener_1);
  btn->attach(listener_2);
  btn->attach(listener_3);
  btn->attach(listener_4);
  client::clientCode(btn);

  std::cout << "Remove listener2\n";
  btn->detach(listener_2);
  client::clientCode(btn);

  delete btn;
  delete listener_1;
  delete listener_2;
  delete listener_3;
  delete listener_4;
}

}  // namespace observer
}  // namespace

#include "ExampleRegistry.h"

class ObserverExample : public IExample {
 public:
  std::string group() const override { return "dp/behavioral"; }
  std::string name() const override { return "Observer"; }
  std::string description() const override {
    return "Observer Pattern Example";
  }
  void execute() override { observer::run(); }
};

REGISTER_EXAMPLE(ObserverExample);