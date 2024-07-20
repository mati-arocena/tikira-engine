#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
#endif

#include "Window.h"
#include "Launch.h"
#include "Log.h"

#include <array>
#include <format>
#include <string>
#include <memory>
#include <iostream>

const int VERTEX_NUMBER = 9;
const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 512;

const float MILLIS = 1000.0F;

GLuint LoadShader(GLenum type, const char *shaderSrc) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSrc, nullptr);
    glCompileShader(shader);
    return shader;
}

void mainLoop() 
{
    std::array<GLfloat, VERTEX_NUMBER> vertices = {
        0.0F, 1.0F, 0.0F,  // Top vertex
        -1.0F,-1.0F, 0.0F,  // Left vertex
        1.0F,-1.0F, 0.0F   // Right vertex
    };

    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, "attribute vec4 position; void main() { gl_Position = position; }");
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, "precision mediump float; void main() { gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); }");

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glUseProgram(program);

    glClearColor(1.0F, 0.0F, 1.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);

    TK_LOG_INFO("Drawing triangle");
}

int main(int argc, char** argv)
{
    TK_LOG_INFO("Starting OpenGL ES 2.0");

    auto window = std::make_shared<tikira::Window>("OpenGL ES 2.0", WINDOW_WIDTH, WINDOW_HEIGHT);
    tikira::Launch launch(window, mainLoop);

#ifndef __EMSCRIPTEN__
    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            {
                quit = true;
            }
        }
        launch.Tick();
    }
#endif

    return 0;
}