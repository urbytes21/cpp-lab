//cppcheck-suppress-file [invalidPointerCast]
#include <fstream>
#include <iostream>
#include <string>
#include "ExampleRegistry.h"

namespace {

// Important: Do not use sizeof() to dump the raw memory of an object if it contains std::string.
class Account {
  friend std::ostream& operator<<(std::ostream&, const Account&);

 private:
  int code;
  std::string name;
  double balance;

 public:
  explicit Account(int c = 0, const std::string& n = "", double b = 0.0)
      : code(c), name(n), balance(b) {}

  int getCode() const { return code; }

  std::ostream& write(std::ostream&) const;
  std::istream& read(std::istream&);
};

std::ostream& Account::write(std::ostream& os) const {
  os.write(reinterpret_cast<const char*>(&code), sizeof(code));
  os.write(reinterpret_cast<const char*>(&balance), sizeof(balance));

  std::size_t length = name.size();
  os.write(reinterpret_cast<const char*>(&length), sizeof(length));
  os.write(name.data(), length);

  return os;
}

std::istream& Account::read(std::istream& is) {
  is.read(reinterpret_cast<char*>(&code), sizeof(code));
  is.read(reinterpret_cast<char*>(&balance), sizeof(balance));

  std::size_t length = 0;
  is.read(reinterpret_cast<char*>(&length), sizeof(length));

  name.resize(length);
  is.read(&name[0], length);

  return is;
}

std::ostream& operator<<(std::ostream& os, const Account& acc) {
  os << "Code   : " << acc.code << "\n";
  os << "Name   : " << acc.name << "\n";
  os << "Balance: " << acc.balance << "\n";
  return os;
}

void run() {

  // ====== WRITE ======
  Account* accounts[2];
  accounts[0] = new Account(1, "Whitney Elizabeth Houston", 2500);
  accounts[1] = new Account(2, "Michael Jackson", 5000);

  std::ofstream outf("data.bin", std::ios::binary | std::ios::trunc);

  if (!outf) {
    std::cerr << "Cannot open file for writing\n";
    return;
  }

  for (int i = 0; i < 2; ++i) {
    if (!accounts[i]->write(outf))
      std::cerr << "Error writing account " << i << "\n";
  }

  outf.close();
  std::cout << "Finish writing.\n";

  // ====== READ ACCOUNT #2 ======
  std::ifstream inf("data.bin", std::ios::binary);

  if (!inf) {
    std::cerr << "Cannot open file for reading\n";
  } else {

    Account* temp = new Account();

    while (inf.peek() != EOF) {
      temp->read(inf);

      if (temp->getCode() == 2) {
        std::cout << "\nAccount #2\n";
        std::cout << *temp << std::endl;
        break;
      }
    }

    delete temp;
  }

  inf.close();

  // ====== CLEAN MEMORY ======
  delete accounts[0];
  delete accounts[1];

  std::cout << "Finish reading.\n";
}
}  // namespace

class BinaryFileHandling : public IExample {
 public:
  std::string group() const override { return "core/filehandle"; }
  std::string name() const override { return "BinaryFileHandling"; }
  std::string description() const override { return "Binary file handling"; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(BinaryFileHandling, "core/filehandle", "BinaryFileHandling");