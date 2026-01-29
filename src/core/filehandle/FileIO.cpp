#include <fstream>
#include <iostream>

namespace {

constexpr inline std::string_view test_file_name = "fileio_test.csv";

void fileInput() {
  std::ifstream inFile{std::string{test_file_name}};
  if (!inFile.is_open()) {
    std::cerr << "Cannot open file: " << test_file_name << " \n";
  }

  std::string inputStr{};
  std::cout << "====skip while space content====" << std::endl;
  while (
      inFile >>
      inputStr) {  //  Note that ifstream returns a 0 if we’ve reached the end of the file (EOF)
    std::cout << inputStr;
  }
  std::cout << "========" << std::endl;
  std::cout << "====full content====" << std::endl;

  // not skip whitespace
  inFile.close();
  inFile.open(std::string{test_file_name});  // explicitly call open()
  // The otherway to do this
  /**
   * inFile.clear();                 // clear eof/fail flags
   * inFile.seekg(0);                // rewind
   */

  inputStr.clear();
  while (std::getline(inFile, inputStr)) {
    std::cout << inputStr << std::endl;
  }
  std::cout << "========" << std::endl;

  inFile.close();
}

void fileOutput() {
  std::ofstream outfile{std::string{
      test_file_name}};  // only output stream creates new file if not exist
  if (!outfile || !outfile.is_open()) {
    std::cerr << "Cannot open file: " << test_file_name << " \n";
    return;
  }

  // Put bytes data to the file
  // put string
  std::string elfBytes{
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
  outfile << elfBytes;

  elfBytes =
      "0x0 0x0"
      "0x0 0x0"
      "0x0 0x0";
  outfile << elfBytes;

  elfBytes =
      "0xF 0xA \
              0xE 0xB \
              0x0 0x0";
  outfile << elfBytes;

  outfile.put('E');  // put char
  outfile.close();
}

void fileRemove() {
  std::remove(std::string{test_file_name}.c_str());
  std::ifstream ifile{std::string{test_file_name}};
  if (ifile) {
    std::cerr << "Cannot delete file: " << test_file_name << " \n";
    return;
  }

  std::cout << "Delete file: " << test_file_name << " \n";
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

struct FileIO {
  FileIO() { run(); }
};

static FileIO autoRunner;