#include "Manager.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>

Manager::~Manager() {
  for (auto it : students_) {
    delete it;
  }
}

void Manager::add() {
  std::string name = inputStr("Name?", "Invalid");
  std::string address = inputStr("Address?", "Invalid");
  Student* s = new Student(name, address);
  students_.push_back(s);
  sortByName();
  std::cout << "Add successful!\n";
}

void Manager::remove() {
  std::string code = inputStr("Code?", "Invalid");
  // for (auto it = students_.begin(); it != students_.end(); ++it) {
  //   if ((*it)->getCode().substr(0, code.size()) == code) {
  //     delete *it;
  //     students_.erase(it);
  //     std::cout << "Remove successfull!\n";
  //     break;
  //   }
  // }
  auto it = std::find_if(
      students_.begin(), students_.end(),
      [&code](const Student* s) { return s && s->getCode().find(code) == 0; });

  if (it != students_.end()) {
    students_.erase(it);
    std::cout << "Remove successfull!\n";
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
  for (const auto* const s : manager.students_) {
    os << *s << "\n";
  }
  return os;
}

Student* Manager::findByCode(const std::string& cod) {
  // for (auto it : students_) {
  //   // if (it->getCode().substr(0, cod.size()) == cod) // partial match
  //   if (it->getCode() == cod) {
  //     return it;
  //   }
  // }
  const auto it = std::find_if(
      students_.begin(), students_.end(),
      [&cod](const Student* s) { return s && s->getCode() == cod; });

  if (it != students_.end()) {
    return *it;
  }

  std::cout << "Student not found !!\n";
  return nullptr;
}

void Manager::sortByName() {
  std::sort(students_.begin(), students_.end(),
            [](const Student* a, const Student* b) { return *a < *b; });
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
  // for (auto it : students_) {
  //   // contain
  //   if (it->getName().find(name) != std::string::npos) {
  //     result.push_back(it);
  //   }
  // }
  std::copy_if(students_.begin(), students_.end(), std::back_inserter(result),
               [&name](const Student* const s) {
                 return s && s->getName().find(name) != std::string::npos;
               });

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