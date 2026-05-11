// Bridge lets we split a large class or a set of closely related classes
// into two separate hierarchies—abstraction and implementation
// which can be developed independently of each other.
// Appicability:
// (*)   when you want to divide and organize a monolithic class that has
// several variants of some functionality
//       (for example, if the class can work with various database servers).
// (**)  when you need to extend a class in several orthogonal (independent)
// dimensions.
// (***) when you you need to be able to switch implementations at runtime.

// UML: docs/uml/patterns_structural_bridge.drawio.svg

#include <memory>
#include <utility>
#include "ExampleRegistry.h"
#include "Logger.h"

namespace {
namespace problem {
class Widget {
 public:
  virtual ~Widget() = default;
  virtual void click_on() const = 0;
};

/* Concrete variations for Button */
class Button : public Widget {
 public:
  void click_on() const override { LOG("executed"); }
};

class ButtonWindows : public Button {
 public:
  void click_on() const override {
    LOG("executed");
    Button::click_on();
  }
};

class ButtonLinux : public Button {
 public:
  void click_on() const override {
    LOG("executed");
    Button::click_on();
  }
};

/* Concrete variations for Label */
class Label : public Widget {
 public:
  void click_on() const override { LOG("executed"); }
};

class LabelWindows : public Label {
 public:
  void click_on() const override {
    LOG("executed");
    Label::click_on();
  }
};

class LabelLinux : public Label {
 public:
  void click_on() const override {
    LOG("executed");
    Label::click_on();
  }
};

void run() {
  LOG("Problem");
  /* Concrete variations for others widgets like Text,CCombo  or new platform
 * macOS etc*/
  // [Problem 1] We have to write the Text/TextLinux ...
  auto client_code = [](const Widget* widget) {
    if (widget != nullptr)
      widget->click_on();
  };

  // [Problem 2] : Use the Bridge if you need to be able to switch
  // implementations at runtime. how to exmaple for this still don't know
  Widget* button = new ButtonWindows();
  client_code(button);
  delete button;
}
}  // namespace problem

namespace bridge_pattern {
/**
 * The Implementation defines the interface for all implementation classes. It
 * doesn't have to match the Abstraction's interface. In fact, the two
 * interfaces can be entirely different. Typically the Implementation interface
 * provides only primitive Widgets, while the Abstraction defines higher-
 * level Widgets based on those primitives.
 */
class OsImplemetation {
 public:
  virtual void click_on_ipl() const = 0;
  virtual ~OsImplemetation() = default;
};

class WindowsImplemetation : public OsImplemetation {
 public:
  void click_on_ipl() const override { LOG("[Windows]"); }
};

class LinuxImplemetation : public OsImplemetation {
 public:
  void click_on_ipl() const override { LOG("[Linux]"); }
};

/**
 * The Abstraction defines the interface for the "control" part of the two class
 * hierarchies. It maintains a reference to an object of the Implementation
 * hierarchy and delegates all of the real work to this object.
 */
class WidgetAbstraction {
 protected:
  std::shared_ptr<OsImplemetation> implementation_;

 public:
  explicit WidgetAbstraction(std::shared_ptr<OsImplemetation> implemetation)
      : implementation_{std::move(implemetation)} {}
  virtual ~WidgetAbstraction() = default;

  virtual void click_on() const = 0;
};

/**
 * We can extend the Abstraction without changing the Implementation classes.
 */
class ButtonAbstraction : public WidgetAbstraction {
 public:
  explicit ButtonAbstraction(std::shared_ptr<OsImplemetation> implemetation)
      : WidgetAbstraction{std::move(implemetation)} {}
  void click_on() const override {
    LOG("executed");
    this->implementation_->click_on_ipl();
  }
};

class LabelAbstraction : public WidgetAbstraction {
 public:
  explicit LabelAbstraction(std::shared_ptr<OsImplemetation> implemetation)
      : WidgetAbstraction{std::move(implemetation)} {}
  void click_on() const override {
    LOG("executed");
    this->implementation_->click_on_ipl();
  }
};

void run() {
  LOG("Bridge Example");
  auto client_code = [](const WidgetAbstraction* widget) {
    if (widget != nullptr)
      widget->click_on();
  };

  std::shared_ptr<OsImplemetation> os =
      std::make_shared<WindowsImplemetation>();
  WidgetAbstraction* widget = new ButtonAbstraction(os);
  client_code(widget);

  os = std::make_shared<LinuxImplemetation>();
  widget = new LabelAbstraction(os);
  client_code(widget);

  delete widget;
}
}  // namespace bridge_pattern

class BridgeExample : public IExample {
 public:
  std::string group() const override { return "dp/structural"; }
  std::string name() const override { return "Bridge"; }
  std::string description() const override { return "Bridge Pattern Example"; }
  void execute() override {
    problem::run();
    bridge_pattern::run();
  }
};

REGISTER_EXAMPLE(BridgeExample);
}  // namespace