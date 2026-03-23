#pragma once
#include <iostream>
#include <string>
class Student {

 public:
  Student(const std::string& name, const std::string& address);
  Student(const Student& other);
  ~Student();

  void setName(const std::string& name);
  void setAddress(const std::string& address);
  void setMark(double mark);

  const std::string& getCode() const;
  const std::string& getAddress() const;
  const std::string& getName() const;
  double getMark() const;

  friend std::ostream& operator<<(std::ostream& os, const Student& student);
  friend bool operator<(const Student& a, const Student& b);

 private:
  void setCode();

 private:
  std::string code_;
  std::string name_;
  std::string address_;
  double mark_;
};