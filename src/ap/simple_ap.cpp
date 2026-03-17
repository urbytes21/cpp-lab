#include <gtkmm.h>
#include <iostream>
#include <string>

// We put everything into a single window class (God Class)
class MainWindow : public Gtk::Window {

  // --- Layout Containers ---
  Gtk::Box m_mainLayout;
  Gtk::Box m_topRowLayout;

  // --- Widgets ---
  // We must declare everything here so that the buttons are accessible

  // Editor
  Gtk::Frame frame_Editor;
  Gtk::Box m_boxEditor;
  Gtk::Entry entry_Input;
  Gtk::Button button_Update;

  // Monitor A
  Gtk::Frame frame_MonitorA;
  Gtk::Box m_boxMonitorA;
  Gtk::Label m_labelMonitorA;

  //  Monitor B
  Gtk::Frame frame_MonitorB;
  Gtk::Box m_boxMonitorB;
  Gtk::Label m_labelMonitorB;

 public:
  MainWindow()
      : m_mainLayout(Gtk::Orientation::VERTICAL),
        m_topRowLayout(Gtk::Orientation::HORIZONTAL),
        m_boxEditor(Gtk::Orientation::VERTICAL),
        m_boxMonitorA(Gtk::Orientation::VERTICAL),
        m_boxMonitorB(Gtk::Orientation::VERTICAL) {
    set_title("No-MVC (Coupled) Demo");
    set_default_size(600, 400);

    // 1. SETUP UI (Visually identical to MVC)
    // --- Monitor A ---
    frame_MonitorA.set_label("ZONE 2: MONITOR A (Blue)");
    m_labelMonitorA.set_markup(
        "<span foreground='blue' size='x-large'>Initial Data</span>");
    m_boxMonitorA.append(m_labelMonitorA);
    frame_MonitorA.set_child(m_boxMonitorA);
    frame_MonitorA.set_hexpand(true);  // Stretch

    // --- Monitor B ---
    frame_MonitorB.set_label("ZONE 3: MONITOR B (Red)");
    m_labelMonitorB.set_markup(
        "<span foreground='red' size='x-large'>Initial Data</span>");
    m_boxMonitorB.append(m_labelMonitorB);
    frame_MonitorB.set_child(m_boxMonitorB);
    frame_MonitorB.set_hexpand(true);

    // --- Editor ---
    frame_Editor.set_label("ZONE 1: EDITOR");
    entry_Input.set_text("Initial Data");
    button_Update.set_label("Direct Update");  // Live updates
    m_boxEditor.append(entry_Input);
    m_boxEditor.append(button_Update);
    frame_Editor.set_child(m_boxEditor);

    // --- Layout ---
    m_topRowLayout.append(frame_MonitorA);
    m_topRowLayout.append(frame_MonitorB);
    m_mainLayout.append(m_topRowLayout);
    m_mainLayout.append(frame_Editor);

    // Margin for aesthetics
    m_boxEditor.set_margin(10);
    m_boxEditor.set_spacing(5);
    m_boxMonitorA.set_margin(20);
    m_boxMonitorB.set_margin(20);
    set_child(m_mainLayout);

    // 2. LOGIC HANDLING
    // Here, the button must "know" exactly who m_labelMonitorA and m_labelMonitorB are.
    // It directly controls the other widgets.
    // (THE BAD PART)
    button_Update.signal_clicked().connect([this]() {
      // Step 1: Get data directly from UI (Entry)
      std::string text = entry_Input.get_text();
      // There may be processing logic here (Validating...)
      if (text.empty())
        return;

      // Step 2: Update Monitor A (Hard-coded) directly
      m_labelMonitorA.set_markup("<span foreground='blue' size='x-large'>" +
                                 text + "</span>");

      // Step 3: Update Monitor B (Hard-coded) directly
      m_labelMonitorB.set_markup("<span foreground='red' size='x-large'>" +
                                 text + "</span>");
      std::cout << "Updated directly without Model!" << std::endl;
    });
  }
};

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create("org.gtkmm.example.nomvc");
  return app->make_window_and_run<MainWindow>(argc, argv);
}