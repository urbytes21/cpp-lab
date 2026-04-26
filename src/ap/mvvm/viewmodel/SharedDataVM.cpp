#include "SharedDataVM.h"

SharedDataVM::SharedDataVM(std::shared_ptr<SharedData> model)
    : model_(std::move(model)) {
  model_->addObserver(this);
}

void SharedDataVM::submitText(const std::string& text) {
  if (text.empty())
    return;

  model_->setData(text);
}

std::string SharedDataVM::getCurrentText() const {
  return model_->getData();
}

void SharedDataVM::addObserver(IObserver* obs) {
  if (obs != nullptr)
    view_observers_.push_back(obs);
}

void SharedDataVM::onDataChanged(const std::string& newData) {
  notifyObservers(newData);
}

void SharedDataVM::notifyObservers(const std::string& data) {
  for (auto* obs : view_observers_) {
    obs->onDataChanged(data);
  }
}