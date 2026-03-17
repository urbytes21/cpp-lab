#include "DisplayWidget.h"

DisplayWidget::DisplayWidget(const std::string& title, const std::string& color,
                             const std::string& startData)
    : Gtk::Box(Gtk::Orientation::VERTICAL),
      innerBox_(Gtk::Orientation::VERTICAL),
      color_(color) {
  frame_.set_label(title);
  frame_.set_margin(10);

  updateLabel(startData);

  innerBox_.append(labelData_);
  innerBox_.set_margin(20);

  frame_.set_child(innerBox_);
  this->append(frame_);
}

void DisplayWidget::updateLabel(const std::string& text) {
  // Escape text to prevent Pango markup injection
  auto escaped = Glib::Markup::escape_text(text);
  std::string markup = "<span foreground='" + color_ +
                       "' size='x-large' weight='bold'>" + escaped + "</span>";
  labelData_.set_markup(markup);
}

void DisplayWidget::onDataChanged(const std::string& newData) {
  updateLabel(newData);
}
