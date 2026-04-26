#pragma once
#include <gtkmm.h>
#include <memory>
#include <string>
#include "../IObserver.h"
#include "../viewmodel/SharedDataViewModel.h"

// DisplayWidget (View):
//   - Read-only monitor that renders the current text value.
//   - Implements IObserver so the ViewModel can push updates.
//   - Has NO knowledge of SharedData or any other model class.
class DisplayWidget : public Gtk::Box, public IObserver {
 public:
  DisplayWidget(const std::string& title, const std::string& color,
                std::shared_ptr<SharedDataViewModel> vm);

  void onDataChanged(const std::string& newData) override;

 private:
  void updateLabel(const std::string& text);

  std::string color_;
  Gtk::Frame frame_;
  Gtk::Box innerBox_;
  Gtk::Label labelData_;

  // The ViewModel reference is kept only to enable self-registration in the
  // constructor.  DisplayWidget never calls commands on it.
  std::shared_ptr<SharedDataViewModel> viewModel_;
};
