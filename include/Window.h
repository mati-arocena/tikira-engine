#pragma once

#include "IModule.h"

#include <memory>

namespace tikira
{

class Window : public IModule {
    public:
        Window(const char* title, int width, int height);
        ~Window();

        void Init() override;
        void Tick() override;
        void Shutdown() override;
    private:
        class WindowImpl;
        std::unique_ptr<WindowImpl> pImpl;

        const char* m_title;
        int m_width;
        int m_height;

        void SwapBuffers();
};

} // namespace tikira
