#pragma once
#include <ctime>
#include <stdexcept>
#include <vector>

class Account {
 public:
  explicit Account(double init = 0.0);
  double getBalance() const;

  void credit(double amount);
  void debit(double amount);
  void viewLog() const;
  std::string toString() const;

 private:
  static const std::string time2Str(time_t t);

 private:
  double balance_;
  std::vector<std::string> log_;
};
