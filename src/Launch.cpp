#include "Launch.h"

#include "Window.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace tikira
{

Launch::~Launch() = default;

Launch::Launch(std::shared_ptr<Window> window, std::function <void()> tick) 
    : m_window(std::move(window)), m_tick(std::move(tick))
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg([](void* arg) {
        static_cast<Launch*>(arg)->Tick();
    }, this, 0, 1);
#endif
}

void Launch::Tick()
{
    m_tick();
    m_window->SwapBuffers();
}

} // namespace tikira
