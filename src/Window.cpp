#include "Window.h"

#include "raylib.h"	

TiKiRa::Window::Window(int width, int height, const std::string& title)
{
    InitWindow(width, height, title.c_str());
}

TiKiRa::Window::~Window()
{
    CloseWindow();
}

bool TiKiRa::Window::IsRunning() const
{
    return !WindowShouldClose();
}
