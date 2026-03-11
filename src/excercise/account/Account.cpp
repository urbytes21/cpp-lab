#include "Account.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

Account::Account(double init) : balance_{init} {
  if (init < 0) {
    throw std::invalid_argument("Invalid credit amount\n");
  }
}

double Account::getBalance() const {
  return balance_;
}

void Account::credit(double amount) {
  if (amount < 0) {
    throw std::invalid_argument("Invalid credit amount\n");
  }
  balance_ += amount;

  std::ostringstream oss;
  std::time_t now = time(NULL);
  oss << std::fixed << std::setprecision(4) << "[credit] " << amount << " at "
      << time2Str(now);
  log_.push_back(oss.str());
}

void Account::debit(double amount) {
  if (amount < 0) {
    throw std::invalid_argument("Invalid debit amount\n");
  }

  double debit_amount = std::min(balance_, amount);
  balance_ -= debit_amount;

  std::ostringstream oss;
  std::time_t now = time(NULL);
  oss << std::fixed << std::setprecision(4) << "[debit] " << debit_amount
      << " at " << time2Str(now);
  log_.push_back(oss.str());
}

void Account::viewLog() const {
  if (log_.empty()) {
    std::cout << "No transactions found.\n";
    return;
  }
  for (const auto& m : log_) {
    std::cout << m << '\n';
  }
}

std::string Account::toString() const {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(4) << "Account balance: " << balance_;
  return oss.str();
}

const std::string Account::time2Str(time_t t) {
  std::string time = ctime(&t);
  time.pop_back();  // remove newline
  return time;
}