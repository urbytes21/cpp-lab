#include <bitset>

#include "ExampleRegistry.h"
#include "Logger.h"

void arithmeticOperator();
void logicalOperator();
void bitWiseOperator();

class Operations : public IExample {
 public:
  std::string group() const override { return "core/basics"; }
  std::string name() const override { return "Operations"; }
  std::string description() const override { return "Operation"; }
  void execute() override {
    arithmeticOperator();
    logicalOperator();
    bitWiseOperator();
  }
};

REGISTER_EXAMPLE(Operations);

void arithmeticOperator() {
  LOG_S("\n--- ArithmeticOperator Examples ---\n");
  int a{100};
  int b{200};

  // Addition
  LOG_S("a = " << a << ", b = " << b);
  int sum = a + b;
  LOG_S("sum = " << sum);

  // Subtraction
  LOG_S("a = " << a << ", b = " << b);
  uint32_t different = a - b;
  LOG_S("different = " << different);

  // Multiplication
  LOG_S("a = " << a << ", b = " << b);
  int product = a * b;
  LOG_S("product = " << product);

  // Division
  LOG_S("a = " << a << ", b = " << b);
  int quotient = a / b;
  LOG_S("quotient = " << quotient);

  // Modulus
  LOG_S("a = " << a << ", b = " << b);
  int remainder = a % b;
  LOG_S("remainder = " << remainder);

  // Increment
  LOG_S("a = " << a);
  int pre_in = ++a;  // increase a, return a
  LOG_S("preIn = " << pre_in);

  LOG_S("a = " << a);
  int post_in = a++;  // copy a to a copy, then increase a, return copy
  LOG_S("postIn = " << post_in);

  // Decrement
  LOG_S("b = " << b);
  int pre_de = --b;
  LOG_S("preDe = " << pre_de);

  LOG_S("b = " << b);
  int post_de = b--;
  LOG_S("postDe = " << post_de);

  // Comma:
  int value = (a++, b);  // a is incremented, then b is returned
  LOG_S("a = " << a << ", b = " << b);
  LOG_S("comma(a++, b) = " << value);
}

void LOG_SicalOperator() {
  LOG("\n--- LOG_SicalOperator Examples ---");
  bool a = true;
  bool b = false;
  bool c = true;

  // show true/false instead of 1/0
  LOG_S(std::boolalpha << "a = " << a << ", b = " << b << ", c = " << c);

  // AND (&&)
  LOG_S("[AND] a && b = " << (a && b));

  // OR (||)
  LOG_S("[OR ] a || b = " << (a || b));

  // NOT (!)
  LOG_S("[NOT] !c = " << (!c));
}

void bitWiseOperator() {
  LOG("\n--- BitWiseOperator Examples ---");
  std::bitset<8> bits_a = 0b1111'1111;  std::bitset<8> bits_b = 0b1111'0000;

  LOG_S("bitA = " << bits_a << ", bitB = " << bits_b);

  // AND
  std::bitset<8> result = bits_a & bits_b;
  LOG_S("bitA && bitB= " << result);

  // OR
  result = bits_a | bits_b;
  LOG_S("bitA | bitB= " << result);

  // XOR
  result = bits_a ^ bits_b;
  LOG_S("bitA ^ bitB= " << result);

  // NOT
  result = ~bits_a;
  LOG_S("~bitA = " << result);

  // LEFT SHIFT
  result = bits_a << 1;
  LOG_S("bitA << 1 = " << result);

  // RIGHT SHIFT
  result = bits_a >> 1;
  LOG_S("bitA >> 1 = " << result);
}