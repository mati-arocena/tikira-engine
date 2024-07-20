#include "Application.h"

#include "Log.h"
#include "Window.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

namespace tikira
{

void Application::Run()
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg([](void* arg) {
        static_cast<Application*>(arg)->TickModules();
        static_cast<Application*>(arg)->Tick();
    }, this, 0, 1);
#else
    while (m_running) {
        TickModules();
        Tick();
    }
#endif
}

void Application::InitModule(const std::shared_ptr<IModule>& module)
{
    module->Init();
    m_modules.push_back(module);
}

void Application::TickModules()
{
    for (auto& module : m_modules) {
        module->Tick();
    }
}

void Application::Shutdown()
{
    m_running = false;

    for (auto& module : m_modules) {
        module->Shutdown();
    }
}

bool Application::IsRunning() const
{
    return m_running;
}

} // namespace tikira
