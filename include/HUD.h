#pragma once

#include <string>


namespace TiKiRa
{
class Vector4;

class HUD
{
public:
    static HUD& GetInstance();

    void DrawText(const std::string& text, int x, int y, int fontSize, const Vector4& color);

    HUD(HUD const&) = delete;
    void operator=(HUD const&) = delete;
private:
    HUD() = default;
    ~HUD() = default;

};    
} // namespace TiKiRa
