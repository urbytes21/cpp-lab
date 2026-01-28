#include <iostream>

#include "version.h"

int main(int argc, char* argv[]) {
  std::cout << std::endl;
  if (__cplusplus == 202302L)
    std::cout << "C++23";
  else if (__cplusplus == 202002L)
    std::cout << "C++20";
  else if (__cplusplus == 201703L)
    std::cout << "C++17";
  else if (__cplusplus == 201402L)
    std::cout << "C++14";
  else if (__cplusplus == 201103L)
    std::cout << "C++11";
  else if (__cplusplus == 199711L)
    std::cout << "C++98";
  else
    std::cout << "pre-standard C++ or an unknown version: " << __cplusplus;
  std::cout << "\n";
  std::cout << APP_NAME << " v" << APP_VERSION << std::endl;
  std::cout << APP_DESCRIPTION << std::endl;
  return 0;
}