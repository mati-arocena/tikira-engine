#pragma once

#include "IModule.h"

#include <memory>
#include <vector>
#include <functional>

namespace tikira
{
class Application
{

public:
    virtual ~Application() = default;

    void InitModule(const std::shared_ptr<IModule>& module);
    void Run();
    void Shutdown();

    virtual void Tick() = 0;

    bool IsRunning() const;
private:
    std::vector<std::shared_ptr<IModule>> m_modules;
    bool m_running = true;

    void TickModules();
};

} // namespace tikira
