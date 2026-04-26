#include "SharedDataVM.h"

mvvm::SharedDataVM::SharedDataVM(std::shared_ptr<SharedData> model)
    : model_(std::move(model)) {
  model_->addObserver(this);
}

void mvvm::SharedDataVM::submitText(const std::string& text) {
  if (text.empty())
    return;

  model_->setData(text);
}

std::string mvvm::SharedDataVM::getCurrentText() const {
  return model_->getData();
}

void mvvm::SharedDataVM::addObserver(IObserver* obs) {
  if (obs != nullptr)
    view_observers_.push_back(obs);
}

void mvvm::SharedDataVM::onDataChanged(const std::string& newData) {
  notifyObservers(newData);
}

void mvvm::SharedDataVM::notifyObservers(const std::string& data) {
  for (auto* obs : view_observers_) {
    obs->onDataChanged(data);
  }
}