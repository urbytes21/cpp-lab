#include <iostream>
#include "ExampleRegistry.h"

#include "Manager.h"

namespace {
void driver_test_student_manager() {
  std::cout << "\n====================\n"
            << __func__ << "\n"
            << "====================\n\n";
  Manager m;
  char c;

  while (true) {
    std::cout << "\n---------- MENU ----------\n";
    std::cout << "C Create a student\n";
    std::cout << "R Retrieve a student\n";
    std::cout << "U Update a student\n";
    std::cout << "D Delete a student\n";
    std::cout << "S Show student list\n";
    std::cout << "Q Quit\n";
    std::cout << "--------------------------\n";

    std::cout << "Your choice: ";
    std::cin >> c;
    std::cin.ignore();

    c = std::toupper(c);

    if (c == 'Q')
      break;

    switch (c) {
      case 'C':
        m.add();
        break;

      case 'R': {
        auto r = m.findByName();
        for (auto s : r)
          std::cout << *s << "\n";
        break;
      }

      case 'U':
        m.update();
        break;
      case 'D':
        m.remove();
        break;
      case 'S':
        std::cout << m;
        break;
    }
  }

  std::cout << "Bye bye!\n";
}
}  // namespace

class DriverStudentManager : public IExample {
 public:
  std::string group() const override { return "excercise"; };
  std::string name() const override { return "DriverStudentManager"; }
  std::string description() const override { return "Test StudentManager"; }

  void execute() override { driver_test_student_manager(); }
};

REGISTER_EXAMPLE(DriverStudentManager, "exercise", "DriverStudentManager")