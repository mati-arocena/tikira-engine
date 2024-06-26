#include "HUD.h"

#include "raylib.h"
#include "TiKiRa.h"

TiKiRa::HUD& TiKiRa::HUD::GetInstance()
{
    static HUD instance;
    return instance;
}

void RayDrawText(const char* text, int posX, int posY, int fontSize, Color color) {
    DrawText(text, posX, posY, fontSize, color);
}

void TiKiRa::HUD::DrawText(const std::string &text, int x, int y, int fontSize, const Color &color)
{
    RayDrawText(text.c_str(), x, y, fontSize, {color.r, color.g, color.b, color.a});
}
