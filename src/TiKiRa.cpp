#include "TiKiRa.h"

#include "Window.h"

#include "raylib.h"

TiKiRa::Engine& TiKiRa::Engine::GetInstance()
{
    static Engine instance;
    return instance;
}

void TiKiRa::Engine::Run(const std::string& title)
{
    Window window(800, 450, title);
    SetTargetFPS(60);

    while (window.IsRunning())    
    {
        TickUpdate();
        TickRender();
    }
}

void TiKiRa::Engine::TickUpdate()
{
    if (Update)
    {
        Update();
    }
}

void TiKiRa::Engine::TickRender()
{
    BeginDrawing();
    ClearBackground({245,245,245,255});
    if (Render)
    {
        Render();
    }
    EndDrawing();
}
