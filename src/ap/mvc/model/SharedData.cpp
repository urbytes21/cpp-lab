#include "SharedData.h"

SharedData::SharedData() : data_{"Initial Data"} {}

void SharedData::setData(const std::string& data) {
  this->data_ = data;
  // Notify observers of the changed data
  notifyObservers();
}

void SharedData::notifyObservers() {
  for (auto o : observers_) {
    o->onDataChanged(this->data_);
  }
}
void SharedData::addObserver(IObserver* obs) {
  if (obs != nullptr)
    observers_.push_back(obs);
}

std::string SharedData::getData() const {
  return data_;
}