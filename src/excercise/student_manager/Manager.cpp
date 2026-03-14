#include "Manager.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>

void Manager::add() {
  std::string name = inputStr("Name?", "Invalid");
  std::string address = inputStr("Address?", "Invalid");
  students_.push_back(std::make_unique<Student>(name, address));
  sortByName();
  std::cout << "Add successful!\n";
}

void Manager::remove() {
  std::string code = inputStr("Code?", "Invalid");
  auto it = std::find_if(
      students_.begin(), students_.end(),
      [&code](const std::unique_ptr<Student>& s) {
        return s && s->getCode().find(code) == 0;
      });

  if (it != students_.end()) {
    students_.erase(it);
    std::cout << "Remove successful!\n";
    return;
  }

  std::cout << "Student not found!\n";
}

void Manager::update() {
  std::string code = inputStr("Code?", "Invalid");
  auto* s = findByCode(code);
  if (s != nullptr) {
    std::cout << "Hint: use old value, press Enter\n";
    std::string name = inputStr("New Name?", "Invalid");
    std::string address = inputStr("New Address?", "Invalid");
    std::string markStr = inputStr("New Mark?", "Invalid");
    double mark{};
    try {
      mark = std::stod(markStr);
    } catch (std::exception& e) {
      std::cout << "invalid mark" << e.what();
    }
    if (mark < 0.0 || mark > 10.0) {
      std::cout << "invalid mark " << mark << "\n";
      return;
    }

    s->setMark(mark);
    s->setName(name);
    s->setAddress(address);
    std::cout << "Update successful! \n";
  }
}

std::ostream& operator<<(std::ostream& os, const Manager& manager) {
  for (const auto& s : manager.students_) {
    os << *s << "\n";
  }
  return os;
}

Student* Manager::findByCode(const std::string& cod) {
  const auto it = std::find_if(
      students_.begin(), students_.end(),
      [&cod](const std::unique_ptr<Student>& s) {
        return s && s->getCode() == cod;
      });

  if (it != students_.end()) {
    return it->get();
  }

  std::cout << "Student not found !!\n";
  return nullptr;
}

void Manager::sortByName() {
  std::sort(students_.begin(), students_.end(),
            [](const std::unique_ptr<Student>& a,
               const std::unique_ptr<Student>& b) { return *a < *b; });
}

std::string Manager::trim(const std::string& str) {
  constexpr std::string_view whitespaces{" \n\r\t\v\x00"};
  auto firstPos = str.find_first_not_of(whitespaces);
  if (firstPos == std::string::npos) {
    return "";
  }

  auto secondPos = str.find_last_not_of(whitespaces);
  return str.substr(firstPos, secondPos - firstPos + 1);
}

std::vector<Student*> Manager::findByName() {
  std::string name = inputStr("Name?", "Invalid Name?");
  std::vector<Student*> result;
  for (const auto& s : students_) {
    if (s && s->getName().find(name) != std::string::npos) {
      result.push_back(s.get());
    }
  }
  return result;
}

std::string Manager::inputStr(const std::string& prompt,
                              const std::string& error) {
  std::string output;
  std::cout << prompt << "\n";
  while (true) {
    if (!std::getline(std::cin, output)) {
      std::cout << "getline failed\n";
      return "";
    }

    output = trim(output);
    if (output != "") {
      return output;
    }
    std::cout << error;
  }
}