#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <sstream>

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

    constexpr const char* kGreen = "\033[32m";
    constexpr const char* kReset = "\033[0m";

    std::cout << "[" << time_buf << "]" << "[" << level << "]" << "[" << file
              << ":" << loc.line() << "]" << "[" << loc.function_name() << "] "
              << kGreen << msg << kReset << '\n';
  }

  // Prevent copies
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

 private:
  Logger() = default;
  std::mutex mutex_;
};

#define LOG(msg) Logger::instance().log(msg)

#define LOG_S(expr)                       \
  do {                                    \
    std::ostringstream oss_;              \
    oss_ << expr;                         \
    std::string s_ = oss_.str();          \
    if (!s_.empty() && s_.back() == '\n') \
      s_.pop_back();                      \
    Logger::instance().log(s_);           \
  } while (0)

#else

inline void LOG(const std::string& msg) {
  std::cout << msg << '\n';
}

inline void LOG_S_IMPL(std::ostringstream& oss) {
  std::string s = oss.str();
  if (!s.empty() && s.back() == '\n')
    s.pop_back();
  std::cout << s << '\n';
}

#define LOG_S(expr)          \
  do {                       \
    std::ostringstream oss_; \
    oss_ << expr;            \
    LOG_S_IMPL(oss_);        \
  } while (0)

#endif
#endif