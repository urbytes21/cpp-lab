#pragma once
#include <memory>
#include <vector>
#include "Student.h"
class Manager {
 public:
  void add();
  void update();
  void remove();
  std::vector<Student*> findByName();

 private:
  void sortByName();
  Student* findByCode(const std::string& cod);
  static std::string trim(const std::string& str);
  static std::string inputStr(const std::string& prompt, const std::string& error);

  friend std::ostream& operator<<(std::ostream& os, const Manager& manager);

 private:
  std::vector<std::unique_ptr<Student>> students_;
};