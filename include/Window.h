#pragma once

#include <string>

namespace TiKiRa
{
    class Window
    {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();

        bool IsRunning() const;
    };
    
} // namespace TiKiRa
