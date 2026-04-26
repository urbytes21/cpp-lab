#include "SharedDataViewModel.h"

SharedDataViewModel::SharedDataViewModel(std::shared_ptr<SharedData> model)
    : model_(std::move(model)) {
  // The ViewModel subscribes to the Model so it receives every change,
  // including changes initiated by other ViewModels in a larger app.
  model_->addObserver(this);
}

// Command: validates input then delegates write to the Model.
// Validation / business rules live here, not in the View.
void SharedDataViewModel::submitText(const std::string& text) {
  if (text.empty())
    return;

  model_->setData(text);
  // onDataChanged() will be called by the Model, which in turn notifies Views.
}

std::string SharedDataViewModel::getCurrentText() const {
  return model_->getData();
}

void SharedDataViewModel::addObserver(IObserver* obs) {
  if (obs != nullptr)
    viewObservers_.push_back(obs);
}

// IObserver implementation: Model calls this after every setData().
// The ViewModel can transform/enrich the data here before pushing it to Views.
void SharedDataViewModel::onDataChanged(const std::string& newData) {
  notifyObservers(newData);
}

void SharedDataViewModel::notifyObservers(const std::string& data) {
  for (auto* obs : viewObservers_) {
    obs->onDataChanged(data);
  }
}
