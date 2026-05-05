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

#include <list>
#include <string>
#include "Logger.h"

namespace {
namespace observer {

enum class Event {
  kCreate = 0,
  kRead,
  kUpdate,
  kDelete,
};

/**
 * @brief Get the Event Name object
 * 
 * This is a static definition in anonymous namespace
 * @param e 
 * @return const char* 
 */
inline std::string getEventName(const Event& e) {
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
  return "UNKNOWN";
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

  virtual std::string get_name() const = 0;
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
    LOG("attched: " + observer->get_name());
    listeners_.push_back(observer);
  }

  void detach(IListenerObserver* observer) override {
    LOG("detached: " + observer->get_name());
    listeners_.remove(observer);
  }

  void notify(const Event& e) override {
    LOG("notify event: " + getEventName(e));
    for (IListenerObserver* o : listeners_) {
      o->update(e);
    }
  }
};

class AbstractListenerObserver : public IListenerObserver {
 private:
  std::string name_;

 protected:
  void log(const Event& e) const {
    LOG(this->get_name() + " updated after event: " + getEventName(e));
  }

 public:
  explicit AbstractListenerObserver(std::string name)
      : name_(std::move(name)) {}

  std::string get_name() const override { return name_; }
};

/**
 * Concrete Subscribers perform some actions in response to notifications issued
 * by the publisher. All of these classes must implement the same interface so
 * the publisher isn’t coupled to concrete classes.
 */
class ConcreteListenerObserverA : public AbstractListenerObserver {
 public:
  void update(const Event& e) override { log(e); }

  explicit ConcreteListenerObserverA(std::string name)
      : AbstractListenerObserver(std::move(name)){};
};

class ConcreteListenerObserverB : public AbstractListenerObserver {
 public:
  explicit ConcreteListenerObserverB(std::string name)
      : AbstractListenerObserver(std::move(name)){};

  void update(const Event& e) override { log(e); }
};

void run() {

  // Client code that triggers event
  auto client_code = [](IWidgetSubject* const widget, const Event& e) {
    widget->notify(e);
  };

  // Create subject - Button
  IWidgetSubject* btn = new ButtonConcreteSubject();

  // Create observers - Listenerss
  IListenerObserver* listener_1 = new ConcreteListenerObserverA("listener 1");
  IListenerObserver* listener_2 = new ConcreteListenerObserverA("listener 2");
  IListenerObserver* listener_3 = new ConcreteListenerObserverA("listener 3");
  IListenerObserver* listener_4 = new ConcreteListenerObserverB("listener 4");

  // Register observers to the subject
  btn->attach(listener_1);
  btn->attach(listener_2);
  btn->attach(listener_3);
  btn->attach(listener_4);

  // Notify all observers
  client_code(btn, Event::kCreate);

  // Unregister one observer
  btn->detach(listener_2);

  // Notify all observers
  client_code(btn, Event::kUpdate);

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