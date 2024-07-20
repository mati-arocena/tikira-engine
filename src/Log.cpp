#include "Log.h"

#ifdef __EMSCRIPTEN__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

namespace tikira
{

    std::mutex Log::log_mutex;

    float Log::GetTime()
    {
        return static_cast<float>(SDL_GetTicks64()) / TO_MILLIS;
    }

} // namespace tikira
