#include <fstream>
#include <iostream>

namespace {

constexpr inline std::string_view kTestFileName = "fileio_test.csv";

void fileInput() {
  std::ifstream in_file{std::string{kTestFileName}};
  if (!in_file.is_open()) {
    std::cerr << "Cannot open file: " << kTestFileName << " \n";
  }

  std::string input_str{};
  std::cout << "====skip while space content====" << std::endl;
  while (
      in_file >>
      input_str) {  //  Note that ifstream returns a 0 if we’ve reached the end of the file (EOF)
    std::cout << input_str;
  }
  std::cout << "========" << std::endl;
  std::cout << "====full content====" << std::endl;

  // not skip whitespace
  in_file.close();
  in_file.open(std::string{kTestFileName});  // explicitly call open()
  // The otherway to do this
  /**
   * inFile.clear();                 // clear eof/fail flags
   * inFile.seekg(0);                // rewind
   */

  input_str.clear();
  while (std::getline(in_file, input_str)) {
    std::cout << input_str << std::endl;
  }
  std::cout << "========" << std::endl;

  in_file.close();
}

void fileOutput() {
  std::ofstream outfile{std::string{
      kTestFileName}};  // only output stream creates new file if not exist
  if (!outfile || !outfile.is_open()) {
    std::cerr << "Cannot open file: " << kTestFileName << " \n";
    return;
  }

  // Put bytes data to the file
  // put string
  std::string elf_bytes{
      R"""(
        time_s,
        gsr_value 0.0, 45.27761157741693 0.005, 41.69912812397066 0.01,
        38.13110177547114 0.015, 35.32162785580394 0.02,
        31.75617843363382 0.025, 28.352875321528607 0.03,
        25.23210282654006 0.035, 21.769688905641132 0.04,
        17.99031153059391 0.045, 15.073732055666543 0.05,
        15.13550182371759 0.055, 14.69547985289048 0.06,
        14.867397107985468 0.065, 14.982082556093832 0.07,
        14.893751010484861 0.075, 14.877034044202343 0.08,
        14.820590581790071 0.085, 15.1065350504897 0.09,
        15.152287796727098 0.095, 14.764395300078201 0.1,
        15.118189654760348 0.105, 15.473255351586635 0.11,
        14.913896402347113
    \n )"""};
  outfile << elf_bytes;

  elf_bytes =
      "0x0 0x0"
      "0x0 0x0"
      "0x0 0x0";
  outfile << elf_bytes;

  elf_bytes =
      "0xF 0xA \
              0xE 0xB \
              0x0 0x0";
  outfile << elf_bytes;

  outfile.put('E');  // put char
  outfile.close();
}

void fileRemove() {
  std::remove(std::string{kTestFileName}.c_str());
  std::ifstream ifile{std::string{kTestFileName}};
  if (ifile) {
    std::cerr << "Cannot delete file: " << kTestFileName << " \n";
    return;
  }

  std::cout << "Delete file: " << kTestFileName << " \n";
}

void run() {
  // Create and produce data to a file
  fileOutput();

  // Load the created file as input and display its content
  fileInput();

  // remove the file
  fileRemove();
}
}  // namespace

#include "ExampleRegistry.h"

class FileIO : public IExample {
 public:
  std::string group() const override { return "core/filehandle"; }
  std::string name() const override { return "FileIO"; }
  std::string description() const override { return ""; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(FileIO);