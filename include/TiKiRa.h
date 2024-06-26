#pragma once

#include <functional>

namespace TiKiRa
{
    class Engine
    {
    public:
        static Engine& GetInstance();
        
        void Run();

        void SetTick(std::function<void(void)> tick) { Tick = tick; }

        Engine(Engine const&) = delete;
        void operator=(Engine const&) = delete;
    private:
        Engine();
        ~Engine();

        std::function<void(void)> Tick;
    };
} // namespace TiKiRa
