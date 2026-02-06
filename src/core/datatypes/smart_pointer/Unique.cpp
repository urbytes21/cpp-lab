#include <cstring>
#include <iostream>
#include <memory>  // for smart ptr

namespace {
class Model {
 private:
  std::unique_ptr<char[]> cstring;

 public:
  explicit Model(const char* s) : cstring{nullptr} {
    if (s) {
      // allocate
      cstring = std::make_unique<char[]>(std::strlen(s) + 1);
      std::strcpy(cstring.get(), s);  // populate
    }
  }

  ~Model() { std::cout << "Model deleted :" << c_str() << "\n"; }
  // Helper functions
  const char* c_str() const  // accessor
  {
    return cstring.get();
  }

  void set_first_char(char ch) {
    if (cstring)
      cstring[0] = ch;
  }
};

void run() {
  std::cout << "\n\nProblem\n";
  Model str1{"str1"};
  Model str2(str1.c_str());
  std::cout << "Before change:\n";
  std::cout << "  str1 = " << str1.c_str() << "\n";
  std::cout << "  str2 = " << str2.c_str() << "\n";

  str2.set_first_char('X');
  std::cout << "\nAfter modifying str2.set_first_char('X'):\n";
  std::cout << "  str1 = " << str1.c_str() << "\n";
  std::cout << "  str2 = " << str2.c_str() << "\n";

  {
    std::cout << "str1-model,str2-model in scope. \n";
    std::unique_ptr<Model> ptr1 = std::make_unique<Model>("str1-model");
    std::unique_ptr<Model> ptr2(new Model("str2-model"));
    std::cout << "  str1-model = " << ptr1->c_str() << "\n";
    std::cout << "  str2-model = " << ptr2->c_str() << "\n";
  }
  std::cout << "str1-model,str2-model out of scope. \n";
}
}  // namespace

struct UniqueRunner {
  UniqueRunner() {
    std::cout << "\n--- Unique Pointer Example ---\n";
    run();
  }
};

static UniqueRunner autoRunner;