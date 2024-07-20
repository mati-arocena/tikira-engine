#pragma once

#include <iostream>
#include <iomanip>

#ifdef __EMSCRIPTEN__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

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
        std::cout << std::fixed;
        std::cout << std::setprecision(3);
        std::cout << "[" << static_cast<float>(SDL_GetTicks64()) / TO_MILLIS << "] ";
        std::cout << LogLevelToString(level);
        LogRecursive(std::forward<Args>(args)...);
        std::cout << "\n";
    }

private:
    static constexpr float TO_MILLIS = 1000.0F;

    inline static const char* LogLevelToString(LogLevel level) {
        switch (level) {
            case LogLevel::Info:    return "[INFO] ";
            case LogLevel::Warning: return "[WARN] ";
            case LogLevel::Error:   return "[ERROR] ";
            default:      return "[UNKNOWN] ";
        }
    }

    static void LogRecursive() {}

    template <typename T, typename... Args>
    static void LogRecursive(T&& arg, Args&&... args) {
        std::cout << arg;
        LogRecursive(std::forward<Args>(args)...);
    }
};


} // namespace tikira
