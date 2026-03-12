#include <iomanip>
#include <iostream>
#include <limits>

#include "Account.h"
#include "ExampleRegistry.h"

namespace {
void driver_test_account() {
  std::cout << "\n====================\n"
            << __func__ << "\n"
            << "====================\n\n";

  Account acc{0.0};
  while (true) {
    std::cout << "=== MENU ===\n";
    std::cout << "1. Deposit\n";
    std::cout << "2. Withdraw\n";
    std::cout << "3. View balance\n";
    std::cout << "4. View transactions\n";
    std::cout << "5. Quit\n";

    std::cout << "Input the choice: ";
    int choice{};
    if (!(std::cin >> choice) || choice < 1 || choice > 5) {
      std::cout << ">> " << "Invalid the choice\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    };

    double amount{};
    if (choice == 1) {
      std::cout << "Input the amount: ";
      if (std::cin >> amount) {
        try {
          acc.credit(amount);
        } catch (std::invalid_argument& e) {
          std::cout << ">> " << e.what() << "\n";
        }
      } else {
        std::cout << ">> Invalid the amount\n";
      }
    } else if (choice == 2) {
      std::cout << "Input the amount: ";
      if (std::cin >> amount) {
        try {
          acc.debit(amount);
        } catch (std::invalid_argument& e) {
          std::cout << ">> " << e.what() << "\n";
        }
      } else {
        std::cout << ">> Invalid the amount\n";
      }
    } else if (choice == 3) {
      std::cout << ">>" << acc.toString() << "\n";
    } else if (choice == 4) {
      std::cout << ">> ";
      acc.viewLog();
      std::cout << "\n";
    } else {
      return;
    }
  }
}
}  // namespace

class DriverAccount : public IExample {
 public:
  std::string group() const override { return "excercise"; };
  std::string name() const override { return "DriverAccount"; }
  std::string description() const override { return "Test Account"; }

  void execute() override { driver_test_account(); }
};

REGISTER_EXAMPLE(DriverAccount, "excercise", "DriverAccount")