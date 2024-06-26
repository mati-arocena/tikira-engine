#include "TiKiRa.h"
#include "raylib.h"

TiKiRa::Engine& TiKiRa::Engine::GetInstance()
{
    static Engine instance;
    return instance;
}

TiKiRa::Engine::Engine()
{
    InitWindow(800, 450, "TiKiRa Engine");
    SetTargetFPS(60);
}

TiKiRa::Engine::~Engine()
{
    CloseWindow();
}

void TiKiRa::Engine::Run()
{
    while (!WindowShouldClose())    
    {
        BeginDrawing();
        ClearBackground({RAYWHITE});
        if (Tick)
        {
            Tick();
        }
        EndDrawing();
    }
}