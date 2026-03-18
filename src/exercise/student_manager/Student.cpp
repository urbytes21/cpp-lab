#include "Student.h"
#include <algorithm>
#include <ctime>

Student::Student(const std::string& name, const std::string& address)
    : code_{}, name_{name}, address_{address}, mark_{0.0} {
  setCode();
}

Student::~Student(){
    
}

Student::Student(const Student& other)
    : code_{other.code_},
      name_{other.name_},
      address_{other.address_},
      mark_{other.mark_} {}

void Student::setCode() {
  // get name code XXX
  std::string nameCode = name_;

  name_.append(3, ' ');  // so, name code at least 3 charactor
  nameCode.resize(3);
  std::replace(nameCode.begin(), nameCode.end(), ' ', 'X');
  std::transform(nameCode.begin(), nameCode.end(), nameCode.begin(), ::toupper);

  // get time code XXXX
  time_t now = time(NULL);
  std::string timeCode = std::to_string(now);
  timeCode = timeCode.substr(timeCode.size() - 3, timeCode.size());
  code_ = nameCode + timeCode;
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
  os << "[" << student.code_ << "] " << student.name_ << " " << student.mark_;
  return os;
}

bool operator<(const Student& a, const Student& b) {
  if (a.name_ != b.name_) {
    return a.name_ < b.name_;
  };
  return a.code_ < b.code_;
}

void Student::setName(const std::string& name) {
  name_ = name;
}

void Student::setAddress(const std::string& address) {
  address_ = address;
}

void Student::setMark(double mark) {
  mark_ = mark;
}

const std::string& Student::getAddress() const{
  return address_;
}

const std::string& Student::getCode() const {
  return code_;
}

const std::string& Student::getName() const {
  return name_;
}

double Student::getMark() const {
  return mark_;
}
