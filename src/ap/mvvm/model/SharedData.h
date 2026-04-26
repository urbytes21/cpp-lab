#pragma once
#include <string>
#include <vector>
#include "../IObserver.h"

class SharedData {
 public:
  SharedData();

  void setData(const std::string& data);
  std::string getData() const;

  void addObserver(IObserver* obs);

 private:
  void notifyObservers();

  std::string data_;
  std::vector<IObserver*> observers_;
};