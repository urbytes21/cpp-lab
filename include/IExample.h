#pragma once
#include <string>
class IExample {
 public:
  virtual ~IExample() = default;

  virtual std::string group() const = 0;
  virtual std::string name() const = 0;
  virtual std::string description() const = 0;

  virtual void run() = 0;
};