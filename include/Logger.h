#pragma once
#include <iostream>
#include <mutex>
#include <source_location>
#include <string_view>

class Logger {
 public:
  static Logger& instance() {
    static Logger logger;  // guaranteed single instance, thread-safe in C++11+
    return logger;
  }

  void log(std::string_view msg,
           std::source_location loc = std::source_location::current()) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "[" << loc.file_name() << "] " << msg << " \t @"
              << loc.function_name() << '\n';
  }

  // Prevent copies
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

 private:
  Logger() = default;
  std::mutex mutex_;
};

#define LOG(msg) Logger::instance().log(msg)