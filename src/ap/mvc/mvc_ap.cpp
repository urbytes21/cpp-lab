#include <gtkmm.h>
#include <memory>
#include "controller/Controller.h"
#include "model/SharedData.h"
#include "view/DisplayWidget.h"
#include "view/EditorWidget.h"

class ContainerWindow : public Gtk::Window {
 public:
  ContainerWindow();

 private:
  // Main Layout
  Gtk::Box mainLayout_;
  Gtk::Box topRowLayout_;  // Horizontal arrangement (2 Displays side-by-side)

  // Model & Controller are shared across all Views,
  // so we should use as shared pointers
  // Model
  std::shared_ptr<SharedData> dataModel_;
  // Controllers
  std::shared_ptr<Controller> controller_;

  // Views
  std::unique_ptr<EditorWidget> editorView_;
  std::unique_ptr<DisplayWidget> displayViewLeft_;
  std::unique_ptr<DisplayWidget> displayViewRight_;
};

ContainerWindow::ContainerWindow()
    : mainLayout_(Gtk::Orientation::VERTICAL),
      topRowLayout_(Gtk::Orientation::HORIZONTAL) {
  set_title("MVC Integrated Demo");
  set_default_size(600, 400);

  // Init MVC
  dataModel_ = std::make_shared<SharedData>();
  controller_ = std::make_shared<Controller>(dataModel_);

  // Create child Views (Widgets)
  editorView_ =
      std::make_unique<EditorWidget>(controller_, dataModel_->getData());

  // Create two displays of different colors for easier viewing
  displayViewLeft_ = std::make_unique<DisplayWidget>(
      "ZONE 2: MONITOR A (Blue)", "blue", dataModel_->getData());
  displayViewRight_ = std::make_unique<DisplayWidget>(
      "ZONE 3: MONITOR B (Red)", "red", dataModel_->getData());

  dataModel_->addObserver(editorView_.get());
  dataModel_->addObserver(displayViewLeft_.get());
  dataModel_->addObserver(displayViewRight_.get());

  // Layout Arrangement (Container)
  // Top Row: 2 Displays side-by-side (evenly spaced)
  displayViewLeft_->set_hexpand(true);
  displayViewRight_->set_hexpand(true);
  topRowLayout_.append(*displayViewLeft_);
  topRowLayout_.append(*displayViewRight_);

  // Bottom Row: Editor
  editorView_->set_vexpand(
      false);  // Editor doesn't need to be stretched too large

  // Combine into Main Layout
  mainLayout_.append(topRowLayout_);  // Add top row
  mainLayout_.append(*editorView_);   // Add bottom row
  set_child(mainLayout_);
}

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create("org.gtkmm.example.singlemvc");
  return app->make_window_and_run<ContainerWindow>(argc, argv);
}
