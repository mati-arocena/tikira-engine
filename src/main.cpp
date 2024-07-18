#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
#endif

#include <array>

const int VERTEX_NUMBER = 9;
const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 512;

GLuint LoadShader(GLenum type, const char *shaderSrc) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSrc, nullptr);
    glCompileShader(shader);
    return shader;
}

void mainLoop(void* mainLoopArg) 
{
    std::array<GLfloat, VERTEX_NUMBER> vertices = {
        0.0F, 1.0F, 0.0F,  // Top vertex
        -1.0F,-1.0F, 0.0F,  // Left vertex
        1.0F,-1.0F, 0.0F   // Right vertex
    };

    auto* pWindow = static_cast<SDL_Window*>(mainLoopArg);
    
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

    SDL_GL_SwapWindow(pWindow);
}

int main(int argc, char** argv)
{
   	SDL_Window *pWindow = 
        SDL_CreateWindow("Hello Triangle Minimal", 
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         WINDOW_WIDTH, WINDOW_HEIGHT, 
                         SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_CreateContext(pWindow);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    void* mainLoopArg = pWindow;

#ifdef __EMSCRIPTEN__
    int fps = 0; // Use browser's requestAnimationFrame
    emscripten_set_main_loop_arg(mainLoop, mainLoopArg, fps, true);
#else

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

        mainLoop(mainLoopArg);
    }

#endif

    return 0;
}