#include <iostream>
#include <bitset>

#include "ExampleRegistry.h"

void arithmeticOperator();
void logicalOperator();
void bitWiseOperator();

class Operations : public IExample {
 public:
  std::string group() const override { return "core"; }
  std::string name() const override { return "Operations"; }
  std::string description() const override { return "Operation"; }
  void execute() override {
    arithmeticOperator();
    logicalOperator();
    bitWiseOperator();
  }
};

REGISTER_EXAMPLE(Operations, "core", "Operations");

void arithmeticOperator() {
  std::cout << "\n--- ArithmeticOperator Examples ---\n";
  int a{100};
  int b{200};

  // Addition
  std::cout << "a = " << a << ", b = " << b << "\n";
  int sum = a + b;
  std::cout << "sum = " << sum << "\n";

  // Subtraction
  std::cout << "a = " << a << ", b = " << b << "\n";
  int different = a - b;
  std::cout << "different = " << different << "\n";

  // Multiplication
  std::cout << "a = " << a << ", b = " << b << "\n";
  int product = a * b;
  std::cout << "product = " << product << "\n";

  // Division
  std::cout << "a = " << a << ", b = " << b << "\n";
  int quotient = a / b;
  std::cout << "quotient = " << quotient << "\n";

  // Modulus
  std::cout << "a = " << a << ", b = " << b << "\n";
  int remainder = a % b;
  std::cout << "remainder = " << remainder << "\n";

  // Increment
  std::cout << "a = " << a << "\n";
  int pre_in = ++a;  // increase a, return a
  std::cout << "preIn = " << pre_in << "\n";

  std::cout << "a = " << a << "\n";
  int post_in = a++;  // copy a to a copy, then increase a, return copy
  std::cout << "postIn = " << post_in << "\n";

  // Decrement
  std::cout << "b = " << b << "\n";
  int pre_de = --b;
  std::cout << "preDe = " << pre_de << "\n";

  std::cout << "b = " << b << "\n";
  int post_de = b--;
  std::cout << "postDe = " << post_de << "\n";

  // Comma:
  int value = (a++, b);  // a is incremented, then b is returned
  std::cout << "a = " << a << ", b = " << b << "\n";
  std::cout << "comma(a++, b) = " << value << "\n";
}

void logicalOperator() {
  std::cout << "\n--- LogicalOperator Examples ---\n";
  bool a = true;
  bool b = false;
  bool c = true;

  std::cout << std::boolalpha;  // show true/false instead of 1/0
  std::cout << "a = " << a << ", b = " << b << ", c = " << c << "\n\n";

  // AND (&&)
  std::cout << "[AND] a && b = " << (a && b) << "\n";

  // OR (||)
  std::cout << "[OR ] a || b = " << (a || b) << "\n";

  // NOT (!)
  std::cout << "[NOT] !c = " << (!c) << "\n";
}

void bitWiseOperator() {
  std::cout << "\n--- BitWiseOperator Examples ---\n";
  std::bitset<8> bits_a {0b1111'1111};
  std::bitset<8> bits_b {0b1111'0000};

  std::cout
  << "bitA = " << bits_a << ", bitB = " << bits_b << "\n";

  // AND
  std::bitset<8> result = bits_a & bits_b;
  std::cout << "bitA && bitB= " << result << "\n";

  // OR
  result = bits_a | bits_b;
  std::cout << "bitA | bitB= " << result << "\n";

  // XOR
  result = bits_a ^ bits_b;
  std::cout << "bitA ^ bitB= " << result << "\n";

  // NOT
  result = ~bits_a;
  std::cout << "~bitA = " << result << "\n";

  // LEFT SHIFT
  result = bits_a << 1;
  std::cout << "bitA << 1 = " << result << "\n";

  // RIGHT SHIFT
  result = bits_a >> 1;
  std::cout << "bitA >> 1 = " << result << "\n";
}