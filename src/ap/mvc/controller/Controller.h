#pragma once
#include <memory>
#include "../model/SharedData.h"

class Controller {
 public:
  explicit Controller(std::shared_ptr<SharedData> model);

  void updateRequest(const std::string& text);

 private:
  std::shared_ptr<SharedData> model_;
};
