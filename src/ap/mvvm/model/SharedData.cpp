#include "SharedData.h"

mvvm::SharedData::SharedData() : data_{"Initial Data"} {}

void mvvm::SharedData::setData(const std::string& data) {
  this->data_ = data;
  notifyObservers();
}

void mvvm::SharedData::notifyObservers() {
  for (auto* o : observers_) {
    o->onDataChanged(this->data_);
  }
}
void mvvm::SharedData::addObserver(IObserver* obs) {
  if (obs != nullptr)
    observers_.push_back(obs);
}

std::string mvvm::SharedData::getData() const {
  return data_;
}