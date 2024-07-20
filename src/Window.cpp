#include "Window.h"

#ifdef __EMSCRIPTEN__
#include <SDL.h>
#include <SDL_opengles2.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
#endif

#include <memory>

namespace tikira
{

class Window::WindowImpl {
public:
    WindowImpl() : m_Window(nullptr, SDL_DestroyWindow), m_Context(nullptr, SDL_GL_DeleteContext) {}
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_Window;
    std::unique_ptr<void, decltype(&SDL_GL_DeleteContext)> m_Context;
};

Window::~Window() = default;

Window::Window(const char* title, int width, int height) 
{
    pImpl = std::make_unique<WindowImpl>();
    pImpl->m_Window.reset(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN));

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    pImpl->m_Context.reset(SDL_GL_CreateContext(pImpl->m_Window.get()));

    glViewport(0, 0, width, height);
}

void Window::SwapBuffers()
{
    SDL_GL_SwapWindow(pImpl->m_Window.get());
}

} // namespace tikira
