#include "Application.h"
#include "Window.h"
#include "Log.h"

#include <array>
#include <format>
#include <string>
#include <memory>
#include <iostream>
#include <vector>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
#endif

const int VERTEX_NUMBER = 18;
const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 512;

GLuint LoadShader(GLenum type, const char *shaderSrc) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSrc, nullptr);
    glCompileShader(shader);
    
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            std::vector<char> infoLog(infoLen);
            glGetShaderInfoLog(shader, infoLen, nullptr, infoLog.data());
            TK_LOG_ERROR("Error compiling shader: ", infoLog.data());
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

void mainLoop() 
{
    std::array<GLfloat, VERTEX_NUMBER> vertices = {
         0.0F,  0.5F, 0.0F,     1.0F, 0.0F, 0.0F,
        -0.5F, -0.5F, 0.0F,     0.0F, 1.0F, 0.0F,
         0.5F, -0.5F, 0.0F,     0.0F, 0.0F, 1.0F
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    const char* vertexShaderSrc = R"(
        attribute vec4 position;
        attribute vec3 color;
        varying vec3 vColor;
        void main() {
            gl_Position = position;
            vColor = color;
        }
    )";

    const char* fragmentShaderSrc = R"(
        precision mediump float;
        varying vec3 vColor;
        void main() {
            gl_FragColor = vec4(vColor, 1.0);
        }
    )";

    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
    
    if (!vertexShader || !fragmentShader) {
        TK_LOG_ERROR("Failed to compile shaders");
        return;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            std::vector<char> infoLog(infoLen);
            glGetProgramInfoLog(program, infoLen, nullptr, infoLog.data());
            TK_LOG_ERROR("Error linking program: ", infoLog.data());
        }
        glDeleteProgram(program);
        return;
    }

    glUseProgram(program);

    glClearColor(0.2F, 0.2F, 0.2F, 1.0F);  // Grey background
    glClear(GL_COLOR_BUFFER_BIT);

    GLint positionLoc = glGetAttribLocation(program, "position");
    GLint colorLoc = glGetAttribLocation(program, "color");

    glEnableVertexAttribArray(positionLoc);
    glEnableVertexAttribArray(colorLoc);

    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 
                         static_cast<void*>(0));
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 
                         reinterpret_cast<void*>(3 * sizeof(GLfloat)));

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(positionLoc);
    glDisableVertexAttribArray(colorLoc);

    glDeleteBuffers(1, &vbo);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(program);
}

class TestApp : public tikira::Application
{
public:
    void Tick() override
    {
#ifndef __EMSCRIPTEN__
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            {
                TK_LOG_INFO("Shutting down...");
                Shutdown();
            }
        }
#endif
        mainLoop();
    }
};

int main()
{
    TK_LOG_INFO("Starting OpenGL ES 2.0");

    TestApp App;

    auto window = std::make_shared<tikira::Window>("OpenGL ES 2.0", WINDOW_WIDTH, WINDOW_HEIGHT);
    App.InitModule(window);

    App.Run();

    return 0;
}