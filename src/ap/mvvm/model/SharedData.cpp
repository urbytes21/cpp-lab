#include "SharedData.h"

SharedData::SharedData() : data_{"Initial Data"} {}

void SharedData::setData(const std::string& data) {
  data_ = data;
  notifyObservers();
}

void SharedData::notifyObservers() {
  for (auto* o : observers_) {
    o->onDataChanged(data_);
  }
}

void SharedData::addObserver(IObserver* obs) {
  if (obs != nullptr)
    observers_.push_back(obs);
}

std::string SharedData::getData() const {
  return data_;
}
