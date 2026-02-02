#include <filesystem>  // for creating dir
#include <iostream>
#include <string>
namespace {
void run() {
  std::filesystem::path path1{"p1"};
  std::filesystem::path path2{"p1/p2"};

  std::cout << "[1] Try create_directory(p1/p2)\n";
  try {
    if (!std::filesystem::create_directory(path2)) {
      std::cout << "    Failed: parent directory does not exist\n";
    }
  } catch (const std::filesystem::filesystem_error& e) {
    std::cout << "    Exception: " << e.what() << '\n';
  }

  std::cout << "[2] Create parent directories: p1\n";
  std::filesystem::create_directories(path1);

  std::cout << "[3] Try create_directory(p1/p2) again\n";
  if (std::filesystem::create_directory(path2)) {
    std::cout << "    Success\n";
  } else {
    std::cout << "    Failed: directory already exists\n";
  }

  std::cout << "[4] Cleanup\n";
  if (std::filesystem::exists(path2)) {
    std::filesystem::remove(path2);
    std::cout << "    Removed p1/p2\n";
  }

  if (std::filesystem::exists(path1)) {
    std::filesystem::remove(path1);
    std::cout << "    Removed p1\n";
  }
}
}  // namespace

struct DirectoryRunner {
  DirectoryRunner() { run(); }
};

static DirectoryRunner autoRunner;