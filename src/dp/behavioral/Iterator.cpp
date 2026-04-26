// Iterator is a behavioral design pattern that lets you traverse elements of a
// collection without exposing its underlying representation (list, stack, tree,
// etc.). Provide a way to access the elements of an aggregate object
// sequentially without exposing its underlying representation. Appicability:
// (*)   when your collection has a complex data structure under the hood, but
// you want to hide its complexity from clients (either for convenience or
// security reasons).
// (**)  reduce duplication of the traversal code across your app.
// (***) when you want your code to be able to traverse different data
// structures or when types of these structures are unknown beforehand.

// UML: docs/uml/patterns_behavioral_iterator.drawio.svg

#include <iostream>
#include <list>
#include <string>
#include <vector>

namespace {
namespace iterator {
class DataModel {
 private:
  int value_;

 public:
  explicit DataModel(int value) : value_{value} {}

  void setValue(int v) { value_ = v; }

  int getValue() const { return value_; }
};

/**
 * Iterator interface: declares the operations required for traversing a
 * collection: fetching the next element, retrieving the current position,
 * restarting iteration, etc.
 */
template <typename T>
class IIterator {
 public:
  virtual bool hasNext() const = 0;
  virtual const T* next() = 0;
  virtual ~IIterator() = default;
};

/**
 * Aggregate interface: declares one or multiple methods for getting iterators
 * compatible with the collection. Note that the return type of the methods must
 * be declared as the iterator interface so that the concrete collections can
 * return various kinds of iterators.
 */
template <typename T>
class IAggregate {
 public:
  virtual IIterator<T>* createIterator() = 0;
  virtual ~IAggregate() = default;
};

/**
 * Concrete Iterator: implement specific algorithms for traversing a collection.
 * The iterator object should track the traversal progress on its own. This
 * allows several iterators to traverse the same collection independently of
 * each other.
 */
template <typename T>
class VectorConcreteIterator : public IIterator<T> {
 private:
  const std::vector<T>& data_;
  size_t currentIndex_{0};

 public:
  explicit VectorConcreteIterator(const std::vector<T>& data) : data_{data} {}

  bool hasNext() const override { return currentIndex_ < data_.size(); }

  const T* next() override {
    if (hasNext()) {
      return &data_[currentIndex_++];
    }

    return nullptr;
  }
};

template <typename T>
class ListConcreteIterator : public IIterator<T> {
 private:
  const std::list<T>& data_;
  typename std::list<T>::const_iterator it_;

 public:
  explicit ListConcreteIterator(const std::list<T>& data)
      : data_(data), it_(data_.begin()) {}

  bool hasNext() const override { return it_ != data_.end(); }

  const T* next() override {
    if (!hasNext())
      return nullptr;
    const T* ptr = &(*it_);
    ++it_;
    return ptr;
  }
};

/**
 * Concrete Aggregate: return new instances of a particular concrete iterator
 * class each time the client requests one.
 */
template <typename T>
class ListConreteAggregate : public IAggregate<T> {
 private:
  std::list<T> data_;

 public:
  void add(const T& i) { data_.push_back(i); }

  IIterator<T>* createIterator() override {
    return new ListConcreteIterator<T>(data_);
  }
};

template <typename T>
class VectorConcreteAggregate : public IAggregate<T> {
 private:
  std::vector<T> data_;

 public:
  void add(const T& i) { data_.push_back(i); }

  IIterator<T>* createIterator() override {
    return new VectorConcreteIterator<T>(data_);
  }
};

/**
 * The Client works with both collections and iterators via their interfaces.
 * This way the client isn’t coupled to concrete classes, allowing you to use
 * various collections and iterators with the same client code.
 */
namespace client {

void clientCode(IAggregate<int>* collection) {
  IIterator<int>* iterator = collection->createIterator();

  if (iterator != nullptr) {
    while (iterator->hasNext()) {
      std::cout << "int: " << *(iterator->next()) << "\n";
    }
  }

  delete iterator;
}

void clientCode(IAggregate<DataModel>* collection) {
  IIterator<DataModel>* iterator = collection->createIterator();

  if (iterator != nullptr) {
    while (iterator->hasNext()) {
      std::cout << "data: " << iterator->next()->getValue() << "\n";
    }
  }
  delete iterator;
}
}  // namespace Client

void run() {
  std::cout << "\nVectorConcreteAggregate\n";
  VectorConcreteAggregate<int> int_collection;
  for (int i = 0; i < 10; ++i) {
    int_collection.add(i);
  }
  client::clientCode(&int_collection);
  std::cout << "\n";
  VectorConcreteAggregate<DataModel> data_collection;
  for (int i = 0; i < 10; ++i) {
    data_collection.add(DataModel(i * 10));
  }
  client::clientCode(&data_collection);

  std::cout << "\nListConreteAggregate\n";
  ListConreteAggregate<int> int_collection2;
  for (int i = 0; i < 10; ++i) {
    int_collection2.add(i);
  }

  client::clientCode(&int_collection2);
  std::cout << "\n";
  ListConreteAggregate<DataModel> data_collection2;
  for (int i = 0; i < 10; ++i) {
    data_collection2.add(DataModel(i * 10));
  }
  client::clientCode(&data_collection2);
}
}  // namespace iterator
}  // namespace

#include "ExampleRegistry.h"

class IteratorExample : public IExample {
 public:
  std::string group() const override { return "dp/behavioral"; }
  std::string name() const override { return "Iterator"; }
  std::string description() const override {
    return "Iterator Pattern Example";
  }
  void execute() override { iterator::run(); }
};

REGISTER_EXAMPLE(IteratorExample, "dp/behavioral", "Iterator");