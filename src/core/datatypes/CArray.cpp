#include <iostream>

#include "ExampleRegistry.h"

void arrayExamples() {
  std::cout << "\n--- Array Examples ---\n";

  const int arr[5] = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; ++i) {
    std::cout << "arr[" << i << "] = " << arr[i] << "\n";
  }

  double matrix[2][3] = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cout << "matrix[" << i << "][" << j << "] = " << matrix[i][j]
                << "\n";
    }
  }
}

class CArray : public IExample {
 public:
  std::string group() const override { return "core"; }
  std::string name() const override { return "CArray"; }
  std::string description() const override { return ""; }
  void execute() override { arrayExamples(); }
};

REGISTER_EXAMPLE(CArray, "core", "CArray");
