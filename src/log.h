#include <iostream>
#include <source_location>
#include <type_traits>

enum class log_category { info, warning, error };
template <log_category CATEGORY>
void log(const std::source_location location, auto &&...args) {
  auto &&out = std::clog;
  if constexpr (CATEGORY == log_category::info) {
    out << "INFO ";
  } else if constexpr (CATEGORY == log_category::warning) {
    out << "WARN ";
  } else // CATEGORY == log_category::error
  {
    out << "ERROR ";
  }

  out << "at ";
  out << location.file_name() << "(" << location.line() << ":"
      << location.column() << ") `" << location.function_name() << "`: ";

  ((out << std::forward<decltype(args)>(args)), ...) << '\n';

  if constexpr (CATEGORY == log_category::error) {
    throw std::runtime_error("Log Error has been called");
  }
}

#define LOG_INFO(...)                                                          \
  log<log_category::info>(std::source_location::current() __VA_OPT__(, )       \
                              __VA_ARGS__)
#define LOG_WARNING(...)                                                       \
  log<log_category::warning>(std::source_location::current() __VA_OPT__(, )    \
                                 __VA_ARGS__)
#define LOG_ERROR(...)                                                         \
  log<log_category::error>(std::source_location::current() __VA_OPT__(, )      \
                               __VA_ARGS__)
#ifdef NDEBUG // release mode
#define LOG_DEBUG_INFO(...)
#define LOG_DEBUG_WARNING(...)
#define LOG_DEBUG_ERROR(...)
#else // debug mode
#define LOG_DEBUG_INFO(...) LOG_INFO(__VA_ARGS__)
#define LOG_DEBUG_WARNING(...) LOG_WARNING(__VA_ARGS__)
#define LOG_DEBUG_ERROR(...) LOG_ERROR(__VA_ARGS__)
#endif
