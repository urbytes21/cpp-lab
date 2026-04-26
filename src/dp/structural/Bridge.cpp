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

#include <iostream>

#include "ExampleRegistry.h"

namespace {
namespace problem {
class Widget {
 public:
  virtual ~Widget() = default;
  virtual std::string clickOn() const = 0;
};

/* Concrete variations for Button */
class Button : public Widget {
 public:
  std::string clickOn() const override { return "Click on: Button\n"; }
};

class ButtonWindows : public Button {
 public:
  std::string clickOn() const override { return "[Linux]" + Button::clickOn(); }
};

class ButtonLinux : public Button {
 public:
  std::string clickOn() const override {
    return "[Windows]" + Button::clickOn();
  }
};

/* Concrete variations for Label */
class Label : public Widget {
 public:
  std::string clickOn() const override { return "Click on: Label\n"; }
};

class LabelWindows : public Label {
 public:
  std::string clickOn() const override {
    return "[Windows]" + Label::clickOn();
  }
};

class LabelLinux : public Label {
 public:
  std::string clickOn() const override { return "[Linux]" + Label::clickOn(); }
};

/* Concrete variations for others widgets like Text,CCombo  or new platform
 * macOS etc*/
// [Problem 1] We have to write the Text/TextLinux ...

namespace client {
void clientCode(const Widget* widget) {
  if (widget != nullptr)
    std::cout << widget->clickOn();
}
}  // namespace client

void run() {
  // [Problem 2] : Use the Bridge if you need to be able to switch
  // implementations at runtime. how to exmaple for this still don't know
  Widget* button = new ButtonWindows();
  client::clientCode(button);
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
  virtual std::string clickOnImplement() const = 0;
  virtual ~OsImplemetation() = default;
};

class WindowsImplemetation : public OsImplemetation {
 public:
  std::string clickOnImplement() const override { return "[Windows]"; }
};

class LinuxImplemetation : public OsImplemetation {
 public:
  std::string clickOnImplement() const override { return "[Linux]"; }
};

/**
 * The Abstraction defines the interface for the "control" part of the two class
 * hierarchies. It maintains a reference to an object of the Implementation
 * hierarchy and delegates all of the real work to this object.
 */
class WidgetAbstraction {
 protected:
  OsImplemetation* implementation_;

 public:
  explicit WidgetAbstraction(OsImplemetation* implemetation)
      : implementation_{implemetation} {}
  virtual ~WidgetAbstraction() = default;

  virtual std::string clickOn() const = 0;
};

/**
 * We can extend the Abstraction without changing the Implementation classes.
 */
class ButtonAbstraction : public WidgetAbstraction {
 public:
  explicit ButtonAbstraction(OsImplemetation* implemetation)
      : WidgetAbstraction{implemetation} {}
  std::string clickOn() const override {
    return this->implementation_->clickOnImplement() + "Click on: Button\n";
  }
};

class LabelAbstraction : public WidgetAbstraction {
 public:
  explicit LabelAbstraction(OsImplemetation* implemetation)
      : WidgetAbstraction{implemetation} {}
  std::string clickOn() const override {
    return this->implementation_->clickOnImplement() + "Click on: Label\n";
  }
};

namespace client {
void clientCode(const WidgetAbstraction* widget) {
  if (widget != nullptr)
    std::cout << widget->clickOn();
}
}  // namespace client

void run() {
  // TODO(phong-nguyen): check memory leak here
  OsImplemetation* os = new WindowsImplemetation();
  WidgetAbstraction* widget = new ButtonAbstraction(os);
  client::clientCode(widget);

  os = new LinuxImplemetation();
  widget = new LabelAbstraction(os);
  client::clientCode(widget);

  delete os;
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

REGISTER_EXAMPLE(BridgeExample, "dp/structural", "Bridge");
}  // namespace