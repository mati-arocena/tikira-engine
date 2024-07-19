#pragma once

#include <memory>

namespace tikira
{
class Window {
    public:
        Window(const char* title, int width, int height);
        ~Window();
        void SwapBuffers();
    private:
        class WindowImpl;
        std::unique_ptr<WindowImpl> pImpl;
};
} // namespace tikira
