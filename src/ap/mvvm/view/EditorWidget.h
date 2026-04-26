#pragma once
#include <gtkmm.h>
#include <memory>
#include "../IObserver.h"
#include "../viewmodel/SharedDataViewModel.h"

// EditorWidget (View):
//   - Renders a text-entry and a submit button.
//   - Calls viewModel_->submitText() on user action  (no Controller).
//   - Implements IObserver so the ViewModel can push updates back into the
//     entry field (e.g. when another part of the app changes the same data).
//   - Has NO knowledge of SharedData or any other model class.
class EditorWidget : public Gtk::Box, public IObserver {
 public:
  explicit EditorWidget(std::shared_ptr<SharedDataViewModel> vm);

  void onDataChanged(const std::string& newData) override;

 private:
  Gtk::Frame frame_;
  Gtk::Box innerBox_;
  Gtk::Label labelTitle_;
  Gtk::Entry entry_;
  Gtk::Button button_;

  std::shared_ptr<SharedDataViewModel> viewModel_;
};
