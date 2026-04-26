#include <gtkmm.h>
#include <memory>
#include "model/SharedData.h"
#include "view/DisplayWidget.h"
#include "view/EditorWidget.h"
#include "viewmodel/SharedDataViewModel.h"

// ContainerWindow wires up the MVVM triad:
//
//   Model ← ViewModel → Views
//
// Key differences from MVC's ContainerWindow:
//   1. No Controller is created.
//   2. No manual addObserver() calls — each View self-registers with the
//      ViewModel during construction.
//   3. Views receive a shared_ptr<SharedDataViewModel>, never a Model pointer.
class ContainerWindow : public Gtk::Window {
 public:
  ContainerWindow();

 private:
  Gtk::Box mainLayout_;
  Gtk::Box topRowLayout_;

  // Model & ViewModel are shared; Views hold a shared_ptr to the ViewModel.
  std::shared_ptr<SharedData> dataModel_;
  std::shared_ptr<SharedDataViewModel> viewModel_;

  // Views own their GTK subtree (unique_ptr).
  std::unique_ptr<EditorWidget> editorView_;
  std::unique_ptr<DisplayWidget> displayViewLeft_;
  std::unique_ptr<DisplayWidget> displayViewRight_;
};

ContainerWindow::ContainerWindow()
    : mainLayout_(Gtk::Orientation::VERTICAL),
      topRowLayout_(Gtk::Orientation::HORIZONTAL) {
  set_title("MVVM Integrated Demo");
  set_default_size(600, 400);

  // Step 1 – construct the Model.
  dataModel_ = std::make_shared<SharedData>();

  // Step 2 – construct the ViewModel; it subscribes to the Model internally.
  viewModel_ = std::make_shared<SharedDataViewModel>(dataModel_);

  // Step 3 – construct Views, passing only the ViewModel.
  //           Each View self-registers as a ViewModel observer.
  editorView_ = std::make_unique<EditorWidget>(viewModel_);
  displayViewLeft_ = std::make_unique<DisplayWidget>(
      "ZONE 2: MONITOR A (Blue)", "blue", viewModel_);
  displayViewRight_ = std::make_unique<DisplayWidget>(
      "ZONE 3: MONITOR B (Red)", "red", viewModel_);

  // Layout (unchanged from MVC).
  displayViewLeft_->set_hexpand(true);
  displayViewRight_->set_hexpand(true);
  topRowLayout_.append(*displayViewLeft_);
  topRowLayout_.append(*displayViewRight_);

  editorView_->set_vexpand(false);

  mainLayout_.append(topRowLayout_);
  mainLayout_.append(*editorView_);
  set_child(mainLayout_);
}

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create("org.gtkmm.example.singlemvvm");
  return app->make_window_and_run<ContainerWindow>(argc, argv);
}
