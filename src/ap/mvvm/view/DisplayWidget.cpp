#include "DisplayWidget.h"

DisplayWidget::DisplayWidget(const std::string& title, const std::string& color,
                             std::shared_ptr<SharedDataViewModel> vm)
    : Gtk::Box(Gtk::Orientation::VERTICAL),
      color_(color),
      innerBox_(Gtk::Orientation::VERTICAL),
      viewModel_(std::move(vm)) {
  frame_.set_label(title);
  frame_.set_margin(10);

  // Initialise label from the ViewModel's current state (not from the Model).
  updateLabel(viewModel_->getCurrentText());

  innerBox_.append(labelData_);
  innerBox_.set_margin(20);

  frame_.set_child(innerBox_);
  this->append(frame_);

  // Self-register: the ViewModel will push future updates to this View.
  viewModel_->addObserver(this);
}

void DisplayWidget::updateLabel(const std::string& text) {
  std::string markup = "<span foreground='" + color_ +
                       "' size='x-large' weight='bold'>" + text + "</span>";
  labelData_.set_markup(markup);
}

void DisplayWidget::onDataChanged(const std::string& newData) {
  updateLabel(newData);
}
