#pragma once

namespace tikira
{

class IModule
{
public:
    virtual ~IModule() = default;

    virtual void Init() = 0;
    virtual void Tick() = 0;
    virtual void Shutdown() = 0;
};

} // namespace tikira
