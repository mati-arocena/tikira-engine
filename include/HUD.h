#pragma once

#include <string>


namespace TiKiRa
{
    struct Color;

    class HUD
    {
    public:
        static HUD& GetInstance();

        void DrawText(const std::string& text, int x, int y, int fontSize, const Color& color);

        HUD(HUD const&) = delete;
        void operator=(HUD const&) = delete;
    private:
        HUD() = default;
        ~HUD() = default;
    };
} // namespace TiKiRa
