// cppcheck-suppress-file []

// Overloading operator-> *.
// Collection item

#include <iostream>
#include "ExampleRegistry.h"
namespace {

class IntCollection {
 private:
  int m_data[3]{10, 20, 30};

 public:
  class Iterator {
   private:
    int* m_ptr;

   public:
    explicit Iterator(int* ptr) : m_ptr(ptr) {}

    int& operator*() {
      std::cout << "int& operator*()\n";
      return *m_ptr;
    }

    int* operator->() {
      std::cout << "int* operator->()\n";
      return m_ptr;
    }

    Iterator& operator++() {
      ++m_ptr;
      return *this;
    }

    bool operator!=(const Iterator& other) const {
      return m_ptr != other.m_ptr;
    }
  };

  Iterator begin() { return Iterator(m_data); }
  Iterator end() { return Iterator(m_data + 3); }
};

void run() {
  IntCollection col;

  for (auto it = col.begin(); it != col.end(); ++it) {
    std::cout << *it << '\n';
  }
}
}  // namespace

class ClassMemberAccessOperator : public IExample {
 public:
  std::string group() const override { return "core/overloading"; }
  std::string name() const override { return "ClassMemberAccessOperator"; }
  std::string description() const override { return ""; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(ClassMemberAccessOperator, "core/overloading",
                 "ClassMemberAccessOperator");