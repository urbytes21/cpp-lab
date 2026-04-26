// Memento is a behavioral design pattern that lets you save and restore the
// previous state of an object without violating encapsulation, captures and
// externalizes an object's internal state Appicability:
// (*)    when you want to produce snapshots of the object’s state to be able to
// restore a previous state of the object.
// (**)   when direct access to the object’s fields/getters/setters violates its
// encapsulation. UML: docs/uml/patterns_behavioral_memento.drawio.svg

#include <cstdlib>  // for std::rand, std::srand
#include <ctime>    // for std::time
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {
namespace memento {
/**
 * Memento interface provides a way to retrieve the memento's metadata, such as
 * creation date or name. However, it doesn't expose the Originator's state.
 */
class IMemento {
 public:
  virtual ~IMemento() = default;

  virtual std::string getName() const = 0;
  virtual std::string getDate() const = 0;
  virtual std::string getState() const = 0;
};

/**
 * Concrete Memento contains the infrastructure for storing the Originator's
 * state.
 */
class ConcreteMemento : public IMemento {
 private:
  std::string state_;
  std::string date_;
  std::string name_;

 public:
  explicit ConcreteMemento(std::string  state) : state_{std::move(state)} {
    // Get current time
    std::time_t now = std::time(nullptr);
    std::tm* t = std::localtime(&now);

    // Format date as YYYYMMDD_HHMMSS
    std::stringstream date_ss;
    date_ss << std::put_time(t, "%Y%m%d_%H%M%S");
    date_ = date_ss.str();

    // Append a random number for uniqueness
    int rand_num = std::rand() % 10000;  // optional: limit size
    std::stringstream name_ss;
    name_ss << "me" << date_ << "_" << rand_num;
    name_ = name_ss.str();
  }

  std::string getName() const override { return name_; };

  std::string getDate() const override { return this->date_; };

  std::string getState() const override { return this->state_; }
};

/**
 * Originator holds some important state that may change over time.
 * It also defines a method for saving the state inside a memento and another
 * method for restoring the state from it.
 */
class Originator {
 private:
  std::string state_;
  int dummy_{};

  // Simulate new state using rand
  std::string generateRandomString(int len = 10) {
    // String literal concatenation
    const char alpha_num[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    int str_len = sizeof(alpha_num) - 1;
    std::string ran_str;
    for (int i = 0; i < len; ++i) {
      ran_str += alpha_num[std::rand() % str_len];
    }
    dummy_++;
    return ran_str;
  }

 public:
  explicit Originator(std::string  state) : state_{std::move(state)} {
    std::cout << "[O]Initial state is: " << this->state_ << "\n";
  }

  void operation() {
    std::cout << "[O]Doing something important.\n";
    this->state_ = this->generateRandomString(30);
    std::cout << "[O]The state has changed to: " << this->state_ << "\n";
  }

  //  Save the current state inside a memento.
  IMemento* save() { return new ConcreteMemento(this->state_); }

  // Restores the Originator's state from a memento object.
  void restore(IMemento* mem) {
    this->state_ = mem->getState();
    std::cout << "[O]The state has restored to: " << this->state_ << "\n";

    delete mem;
  }
};

/**
 * The Caretaker doesn't depend on the Concrete Memento class. Therefore, it
 * doesn't have access to the originator's state, stored inside the memento. It
 * works with all mementos via the base Memento interface.
 */
class CareTaker {
 private:
  std::vector<IMemento*> mementos_;
  Originator* originator_;

 public:
  explicit CareTaker(Originator* const org) : originator_{org} {}
  ~CareTaker() {
    for (IMemento* m : mementos_) {
      delete m;
    }
  }

  void backup() {
    std::cout << "[C]Saving Originator's state...\n";
    this->mementos_.push_back(this->originator_->save());
  }

  void undo() {
    if (this->mementos_.size() != 0) {
      IMemento* mem = mementos_.back();
      this->mementos_.pop_back();

      std::cout << "[C]Restoring state to: " << mem->getName() << "\n";
      this->originator_->restore(mem);
    }
  }

  void history() const {
    std::cout << "[C]The list of mementos:\n";
    for (const IMemento* m : mementos_) {
      std::cout << "\t" << m->getName() << "\n";
    }
  }
};

namespace client {
void clientCode(Originator* const org) {
  auto* care_taker = new CareTaker(org);

  // 1
  care_taker->backup();
  org->operation();

  // 2
  care_taker->backup();
  org->operation();

  // 3
  care_taker->backup();
  org->operation();

  care_taker->history();
  care_taker->undo();
  care_taker->undo();
  care_taker->history();
  care_taker->undo();

  // [P] The previous state can’t be restored directly because state is
  // private. We need a Memento to save and recover internal state safely.
}
}  // namespace client

void run() {
  // Gen seed
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  auto* origin = new Originator("Hello World");
  client::clientCode(origin);

  delete origin;
}
}  // namespace memento
}  // namespace

#include "ExampleRegistry.h"

class MementoExample : public IExample {
 public:
  std::string group() const override { return "dp/behavioral"; }
  std::string name() const override { return "Memento"; }
  std::string description() const override {
    return "Memento Pattern Example ";
  }
  void execute() override { memento::run(); }
};

REGISTER_EXAMPLE(MementoExample, "dp/behavioral", "Memento");