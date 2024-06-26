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

        void SetRenderFunction(std::function<void(void)> renderFunction) { Render = renderFunction; }
        void SetUpdateFunction(std::function<void(void)> updateFunction) { Update = updateFunction; }
        
        Engine(Engine const&) = delete;
        void operator=(Engine const&) = delete;
    private:
        Engine() = default;
        ~Engine() = default;

        std::function<void(void)> Render;
        std::function<void(void)> Update;
    
        void TickUpdate();
        void TickRender();
    };

    struct Color
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
} // namespace TiKiRa
