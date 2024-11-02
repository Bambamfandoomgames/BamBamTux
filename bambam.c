#include<stdlib.h>
#include<time.h>
#include "raylib.h"
#define NMAX 50

struct fig {
    Vector2 pos;
    double time;
} V[NMAX];

int n=0;

int main(void)
{
    SetRandomSeed(time(NULL));

    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Bam Bam - Linux Logos");

    
    Image tux = LoadImage("resources/img/Tux.png");
    ImageResize(&tux,tux.width/2,tux.height/2);
    Texture2D texture = LoadTextureFromImage(tux);
    UnloadImage(tux);

    SetTargetFPS(60);

    int x = GetRandomValue(0,screenWidth-texture.width);
    int y = GetRandomValue(0,screenHeight-texture.height);

    while (!WindowShouldClose())
    {
        // Update
        if(IsKeyPressed(KEY_T) && n<NMAX)
        {
            V[n].pos.x = GetRandomValue(0,screenWidth-texture.width);
            V[n].pos.y = GetRandomValue(0,screenHeight-texture.height);
            V[n].time = GetTime();
            ++n;
        }

        // Draw
        BeginDrawing();

            ClearBackground(WHITE);

            for(int i=0;i<n;i++)
            {
                if(GetTime()-V[i].time < 5)
                    DrawTexture(texture, V[i].pos.x, V[i].pos.y, WHITE);
                else
                {
                    if(n>1)
                    {
                    struct fig x = V[i];
                    V[i] = V[n-1];
                    V[n-1] = x;
                    }
                    --n;
                }
            }

        EndDrawing();
    }

    UnloadTexture(texture);

    CloseWindow();

    return 0;
}
