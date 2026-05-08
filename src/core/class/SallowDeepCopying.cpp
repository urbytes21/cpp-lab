// cppcheck-suppress-file [noCopyConstructor, noOperatorEq, unsafeClassCanLeak]

#include <iostream>

namespace {
namespace shallow {
class Model {
 private:
  int x_{0}, y_{1};
  int* ptr_{};

 public:
  // Default constructor: Model a = Model(1,2)
  explicit Model(int x, int y, int z) : x_{x}, y_{y} {
    ptr_ = new int;
    *ptr_ = z;
  }

  ~Model() {
    // [P1]
    // Shallow copying makes both objects use the same pointer.
    // If one object deletes the pointer, the other object now
    // points to invalid memory.
    // delete ptr_;   // Commented out on purpose for demo
  }

  void changePtr(int value) {
    if (ptr_ != nullptr) {
      *ptr_ = value;
    }
  }

  int getPtr() const {
    if (ptr_ != nullptr) {
      return *ptr_;
    }
    return 0;
  }

  // Implicit copy constructor: Model a{b};
  // Model(const Model &f) : x_{f.x_}, y_{f.y_} {}

  // Implicit assignment operator (like the way compiler gen this function):
  // Model a = b; Model &operator=(const Model &f)
  // {
  //     // self-assignment guard
  //     if (this == &f)
  //     {
  //         return *this;
  //     }

  //     // do the copy
  //     x_ = f.x_;
  //     y_ = f.y_;

  //     //  return the existing object so we can chain this operator
  //     return *this;
  // }
};

void run() {
  Model obj1 = Model(1, 2, 3);
  Model obj2 = obj1;
  obj2.changePtr(30);
  // [P2]
  std::cout << "\n=== Shallow Copy Demo ===\n";
  std::cout << "obj1.ptr_ = " << obj1.getPtr() << "\n";
  std::cout << "obj2.ptr_ = " << obj2.getPtr() << "\n";
}

}  // namespace shallow

// To do a deep copy on any non-null pointers being copied
// Requires that we write our own `copy constructors` and `overloaded assignment
// operators`.
namespace deep_copying {
class Model {
 private:
  int x_{0}, y_{1};
  int* ptr_{};

  void deepCopy(const Model& source) {
    // sallow copy the normal fields
    x_ = source.x_;
    y_ = source.y_;

    // deep copy the ptr_ field
    // m_data is a pointer, so we need to deep copy it if it is non-null
    // first we need to deallocate any value that this Model is holding!
    delete ptr_;
    if (source.ptr_ != nullptr) {
      // allocate memory for our copy
      ptr_ = new int;
      // do the copy
      *ptr_ = *source.ptr_;
    } else {
      ptr_ = nullptr;
    }
  }

 public:
  // Constructor
  explicit Model(int x, int y, int z) : x_{x}, y_{y} {
    ptr_ = new int;
    *ptr_ = z;
  }

  // Destructor
  ~Model() { delete ptr_; }

  // Copy constructor
  // no need to check self-copy [if (this != &source)]
  // because it cannot happen a(a);
  Model(const Model& source) { this->deepCopy(source); }

  // Assignment operator
  // need to check self-copy [if (this != &source)]
  // because it posible a = a;
  Model& operator=(const Model& source) {
    if (this != &source) {
      // now do the deep copy
      this->deepCopy(source);
    }
    return *this;
  }

  void changePtr(int value) {
    if (ptr_ != nullptr) {
      *ptr_ = value;
    }
  }

  int getPtr() const {
    if (ptr_ != nullptr) {
      return *ptr_;
    }
    return 0;
  }
};

void run() {
  Model obj1 = Model(1, 2, 3);
  Model obj2 = obj1;
  obj2.changePtr(30);

  std::cout << "\n=== Deep Copy Demo ===\n";
  std::cout << "obj1.ptr_ = " << obj1.getPtr() << "\n";
  std::cout << "obj2.ptr_ = " << obj2.getPtr() << "\n";
}

}  // namespace deep_copying
}  // namespace

#include "ExampleRegistry.h"

class ShallowDeepCopying : public IExample {
 public:
  std::string group() const override { return "core"; }
  std::string name() const override { return "ShallowDeepCopying"; }
  std::string description() const override { return ""; }
  void execute() override {
    shallow::run();
    deep_copying::run();
  }
};

REGISTER_EXAMPLE(ShallowDeepCopying);