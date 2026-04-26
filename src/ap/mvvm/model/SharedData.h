#pragma once
#include <string>
#include <vector>
#include "../IObserver.h"

// Model: owns and persists the raw application data.
// It knows nothing about the UI or the ViewModel.
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
