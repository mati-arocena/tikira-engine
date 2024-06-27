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

    Camera camera;
    camera.position = { 1.5f, 1.5f, 1.5f };    // Camera position
    camera.target = { 0.0f, 0.4f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Vector3 position = { 0.0f, 0.0f, 0.0f };  // Set model position

    char modelFileName[] = "../assets/crappy_bird.m3d";
    bool drawMesh = true;
    bool drawSkeleton = true;
    bool animPlaying = false;

    Model model = LoadModel(modelFileName);                 // Load model

    // Load animations
    int animsCount = 0;
    int animFrameCounter = 0, animId = 0;
    ModelAnimation *anims = LoadModelAnimations(modelFileName, &animsCount); // Load skeletal

    while (window.IsRunning())    
    {
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        TickUpdate();
        //TickRender();
         if (animsCount)
        {
            // Play animation when spacebar is held down (or step one frame with N)
            if (IsKeyDown(KEY_SPACE) || IsKeyPressed(KEY_N))
            {
                animFrameCounter++;

                if (animFrameCounter >= anims[animId].frameCount) animFrameCounter = 0;

                UpdateModelAnimation(model, anims[animId], animFrameCounter);
                animPlaying = true;
            }

            // Select animation by pressing C
            if (IsKeyPressed(KEY_C))
            {
                animFrameCounter = 0;
                animId++;

                if (animId >= (int)animsCount) animId = 0;
                UpdateModelAnimation(model, anims[animId], 0);
                animPlaying = true;
            }
        }

        // Toggle skeleton drawing
        if (IsKeyPressed(KEY_B)) drawSkeleton ^= 1;

        // Toggle mesh drawing
        if (IsKeyPressed(KEY_M)) drawMesh ^= 1;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground({245,245,245,255});

            BeginMode3D(camera);

                // Draw 3d model with texture
                if (drawMesh) DrawModel(model, position, 1.0f, {255,255,255,255});

                // Draw the animated skeleton
                if (drawSkeleton)
                {
                    // Loop to (boneCount - 1) because the last one is a special "no bone" bone,
                    // needed to workaround buggy models
                    // without a -1, we would always draw a cube at the origin
                    for (int i = 0; i < model.boneCount - 1; i++)
                    {
                        // By default the model is loaded in bind-pose by LoadModel().
                        // But if UpdateModelAnimation() has been called at least once
                        // then the model is already in animation pose, so we need the animated skeleton
                        if (!animPlaying || !animsCount)
                        {
                            // Display the bind-pose skeleton
                            DrawCube(model.bindPose[i].translation, 0.04f, 0.04f, 0.04f, {255, 0, 0, 255});

                            if (model.bones[i].parent >= 0)
                            {
                                DrawLine3D(model.bindPose[i].translation,
                                    model.bindPose[model.bones[i].parent].translation, {255, 0, 0, 255});
                            }
                        }
                        else
                        {
                            // Display the frame-pose skeleton
                            DrawCube(anims[animId].framePoses[animFrameCounter][i].translation, 0.05f, 0.05f, 0.05f, {255, 0, 0, 255});

                            if (anims[animId].bones[i].parent >= 0)
                            {
                                DrawLine3D(anims[animId].framePoses[animFrameCounter][i].translation,
                                    anims[animId].framePoses[animFrameCounter][anims[animId].bones[i].parent].translation, {255, 0, 0, 255});
                            }
                        }
                    }
                }

                DrawGrid(10, 1.0f);         // Draw a grid

            EndMode3D();

            DrawText("PRESS SPACE to PLAY MODEL ANIMATION", 10, GetScreenHeight() - 80, 10, {0, 0, 0, 255});
            DrawText("PRESS N to STEP ONE ANIMATION FRAME", 10, GetScreenHeight() - 60, 10, {0, 0, 0, 255});
            DrawText("PRESS C to CYCLE THROUGH ANIMATIONS", 10, GetScreenHeight() - 40, 10, {0, 0, 0, 255});
            DrawText("PRESS M to toggle MESH, B to toggle SKELETON DRAWING", 10, GetScreenHeight() - 20, 10, {0, 0, 0, 255});

        EndDrawing();
    }

    UnloadModelAnimations(anims, animsCount);

    UnloadModel(model);         // Unload model
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
