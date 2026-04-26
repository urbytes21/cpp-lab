#pragma once

#include <string>
class IObserver {
 public:
  virtual ~IObserver() = default;
  virtual void onDataChanged(const std::string& newData) = 0;
};