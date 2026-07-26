// cppcheck-suppress-file [functionConst]

// Overloading operator new, delete
// Debug

#include <iostream>
#include "ExampleRegistry.h"
namespace {

class IntCollection {
 private:
  int m_data_[3]{10, 20, 30};

 public:
  class Iterator {
   private:
    int* m_ptr_;

   public:
    explicit Iterator(int* ptr) : m_ptr_(ptr) {}

    int& operator*() { return *m_ptr_; }

    int* operator->() { return m_ptr_; }

    Iterator& operator++() {
      ++m_ptr_;
      return *this;
    }

    bool operator!=(const Iterator& other) const {
      return m_ptr_ != other.m_ptr_;
    }
  };

  Iterator begin() { return Iterator(m_data_); }
  Iterator end() { return Iterator(m_data_ + 3); }

  // int* a = new int;
  void* operator new(size_t size) {
    std::cout << "void* operator new(size_t size)\n";
    // void* p = ::operator new(size);
    void* p = malloc(size);
    if (!p)
      throw std::bad_alloc();
    return p;
  }

  // delete a
  void operator delete(void* p) {
    std::cout << "void operator delete(void* p)\n";
    free(p);
  }

  // int* as = new int[100]
  void* operator new[](size_t size) {
    std::cout << "void* operator new[](size_t size)\n";
    void* p = malloc(size);
    if (!p)
      throw std::bad_alloc();
    return p;
  }

  // delete []as;
  void operator delete[](void* p) {
    std::cout << "void operator delete[](void* p)\n";
    free(p);
  }
};

void run() {
  auto* col = new IntCollection;

  for (auto it = col->begin(); it != col->end(); ++it) {
    std::cout << *it << '\n';
  }

  delete col;

  auto* cols = new IntCollection[10];
  for (int i = 0; i < 10; ++i) {
    for (auto it = cols[i].begin(); it != cols[i].end(); ++it) {
      std::cout << *it << '\n';
    }
  }
  delete[] cols;
}
}  // namespace

class AllocationOperator : public IExample {
 public:
  std::string group() const override { return "core/overloading_operator"; }
  std::string name() const override { return "AllocationOperator"; }
  std::string description() const override { return ""; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(AllocationOperator);