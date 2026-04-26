#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../IObserver.h"
#include "../model/SharedData.h"

// ViewModel: the single mediator between the Model and all Views.
//
// Responsibilities:
//   - Subscribes to the Model (implements IObserver) so it receives every
//     raw-data change and can transform / validate before forwarding.
//   - Exposes a command (submitText) that Views call on user actions.
//     This absorbs what was the Controller in MVC.
//   - Maintains its own observer list so Views subscribe to the ViewModel
//     instead of the Model.  Views never touch SharedData directly.
//
// What the ViewModel must NOT do:
//   - Import any GTK / UI headers.
//   - Know which widgets exist or how they render data.
class SharedDataViewModel : public IObserver {
 public:
  explicit SharedDataViewModel(std::shared_ptr<SharedData> model);

  // ----- Commands (called by View on user input) -----

  // Validate and forward a text update to the Model.
  void submitText(const std::string& text);

  // ----- Queries (called by View to read current state) -----

  std::string getCurrentText() const;

  // ----- View-side observer registration -----

  // Views register here; they receive onDataChanged when the ViewModel's
  // observable state changes (i.e. after the Model confirms the update).
  void addObserver(IObserver* obs);

 private:
  // IObserver: receives raw-data notifications from the Model.
  void onDataChanged(const std::string& newData) override;

  void notifyObservers(const std::string& data);

  std::shared_ptr<SharedData> model_;
  std::vector<IObserver*> viewObservers_;
};
