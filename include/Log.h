#pragma once

#include <iostream>
#include <iomanip>
#include <mutex>
#include <sstream>

#ifdef TK_DEBUG
#define TK_LOG_INFO(...) tikira::Log::LogMessage(tikira::LogLevel::Info, __VA_ARGS__)
#define TK_LOG_WARNING(...) tikira::Log::LogMessage(tikira::LogLevel::Warning, __VA_ARGS__)
#define TK_LOG_ERROR(...) tikira::Log::LogMessage(tikira::LogLevel::Error, __VA_ARGS__)
#else
#define TK_LOG_INFO(...)
#define TK_LOG_WARNING(...)
#define TK_LOG_ERROR(...)
#endif

namespace tikira
{

enum class LogLevel
{
    Info,
    Warning,
    Error
};

class Log
{
public:
    template <typename... Args>
    static void LogMessage(LogLevel level, Args&&... args) {
        std::ostringstream oss;
        oss << std::fixed;
        oss << std::setprecision(3);
        oss << "[" << GetTime() << "] ";
        oss << LogLevelToString(level);
        LogRecursive(oss, std::forward<Args>(args)...);
        oss << "\n";
        std::lock_guard<std::mutex> lock(log_mutex);
        std::cout << oss.str();
    }

private:
    static std::mutex log_mutex;
    static constexpr float TO_MILLIS = 1000.0F;

    inline static const char* LogLevelToString(LogLevel level) {
        switch (level) {
            case LogLevel::Info:    return "[INFO] ";
            case LogLevel::Warning: return "[WARN] ";
            case LogLevel::Error:   return "[ERROR] ";
            default:                return "[UNKNOWN] ";
        }
    }

    static void LogRecursive(std::ostringstream& oss) {}

    template <typename T, typename... Args>
    static void LogRecursive(std::ostringstream& oss, T&& arg, Args&&... args) {
        oss << arg;
        LogRecursive(oss, std::forward<Args>(args)...);
    }

    static float GetTime();
};

} // namespace tikira
