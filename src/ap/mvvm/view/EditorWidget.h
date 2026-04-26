#pragma once
#include <gtkmm.h>
#include <memory>
#include "../IObserver.h"
#include "../viewmodel/SharedDataVM.h"

namespace mvvm {
class EditorWidget : public Gtk::Box, public IObserver {
 public:
  explicit EditorWidget(std::shared_ptr<SharedDataVM> vm);

  void onDataChanged(const std::string& newData) override;

 private:
  Gtk::Frame frame_;
  Gtk::Box innerBox_;
  Gtk::Label labelTitle_;
  Gtk::Entry entry_;
  Gtk::Button button_;

  std::shared_ptr<SharedDataVM> view_model_;
};
}  // namespace mvvm