#pragma once
#include <memory>
#include <vector>
#include "../IObserver.h"
#include "../model/SharedData.h"

/**
 * @brief The single mediator between the Model and all Views 
 *
 * Responsibilities:
 *  - Subscribes to the Model
 *  - Exposes a command that Views call on user actions
 *  - Maintains its own observer list so View subcribe to the ViewModel instead of the Model. View never touch Model
 */
class SharedDataVM : public IObserver {
 public:
  explicit SharedDataVM(std::shared_ptr<SharedData> model);

  void submitText(const std::string& text);

  std::string getCurrentText() const;

  void addObserver(IObserver* obs);

 private:
  void onDataChanged(const std::string& newData) override;
  void notifyObservers(const std::string& data);

  std::shared_ptr<SharedData> model_;       // SharedData model
  std::vector<IObserver*> view_observers_;  // Views
};