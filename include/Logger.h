#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>

#ifndef NDEBUG
#include <mutex>
#include <source_location>
#include <string_view>

class Logger {
 public:
  static Logger& instance() {
    static Logger logger;  // guaranteed single instance, thread-safe in C++11+
    return logger;
  }

  void log(std::string_view msg, std::string_view level = "INFO",
           std::source_location loc = std::source_location::current()) {
    std::lock_guard<std::mutex> lock(mutex_);

    // Extract filename only (no full path)
    std::string_view file = loc.file_name();
    auto pos = file.find_last_of("/\\");
    if (pos != std::string_view::npos) {
      file = file.substr(pos + 1);
    }

    // Get current time
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    localtime_r(&t, &tm);

    char time_buf[9];
    std::strftime(time_buf, sizeof(time_buf), "%H:%M:%S", &tm);

    std::cout << "[" << time_buf << "]" << "[" << level << "]" << "[" << file
              << ":" << loc.line() << "]" << "[" << loc.function_name() << "] "
              << msg << '\n';
  }

  // Prevent copies
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

 private:
  Logger() = default;
  std::mutex mutex_;
};

#define LOG(msg) Logger::instance().log(msg)

#else

inline void LOG(const std::string& msg) {
  std::cout << msg << '\n';
}

#endif
#endif