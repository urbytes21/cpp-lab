#include "EditorWidget.h"

EditorWidget::EditorWidget(std::shared_ptr<SharedDataViewModel> vm)
    : Gtk::Box(Gtk::Orientation::VERTICAL),
      innerBox_(Gtk::Orientation::VERTICAL),
      viewModel_(std::move(vm)) {
  frame_.set_label("ZONE 1: EDITOR (Input View)");
  frame_.set_margin(10);

  labelTitle_.set_text("Enter new data:");
  entry_.set_text(viewModel_->getCurrentText());
  button_.set_label("Broadcast Update");

  innerBox_.append(labelTitle_);
  innerBox_.append(entry_);
  innerBox_.append(button_);
  innerBox_.set_margin(15);
  innerBox_.set_spacing(10);

  frame_.set_child(innerBox_);
  this->append(frame_);

  // MVVM binding: user action → ViewModel command.
  // The View calls a command on the ViewModel; it does not touch the Model.
  button_.signal_clicked().connect(
      [this]() { viewModel_->submitText(entry_.get_text()); });

  // Self-register so the ViewModel can push updates back into this View.
  viewModel_->addObserver(this);
}

void EditorWidget::onDataChanged(const std::string& newData) {
  if (entry_.get_text() != Glib::ustring(newData)) {
    entry_.set_text(newData);
  }
}
