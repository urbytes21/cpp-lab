#include <gtkmm.h>
#include "../IObserver.h"
#include "../controller/Controller.h"
class DisplayWidget : public Gtk::Box, public IObserver {
 public:
  DisplayWidget(const std::string& title, const std::string& color,
                const std::string& startData);

  void onDataChanged(const std::string& newData) override;

 private:
  void updateLabel(const std::string& text);
  Gtk::Frame frame_;
  Gtk::Box innerBox_;
  Gtk::Label labelData_;
  std::string color_;
};