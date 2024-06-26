#pragma once

#include <functional>
#include <string>

namespace TiKiRa
{
    class Engine
    {
    public:
        static Engine& GetInstance();
        
        void Run(const std::string& title);

        void SetTick(std::function<void(void)> tick) { Tick = tick; }

        Engine(Engine const&) = delete;
        void operator=(Engine const&) = delete;
    private:
        Engine() = default;
        ~Engine() = default;

        std::function<void(void)> Tick;
    };

    struct Color
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
} // namespace TiKiRa
