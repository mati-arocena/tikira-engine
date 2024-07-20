#pragma once

#include <memory>
#include <functional>


namespace tikira
{

class Window;

class Launch
{
public:
    Launch(std::shared_ptr<Window> window, std::function <void()> tick);
    ~Launch();
    void Tick();
private:
    std::shared_ptr<Window> m_window;
    std::function <void()> m_tick;
};
    
} // namespace tikira
