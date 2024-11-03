#include<time.h>
#include "raylib.h"

#define NMAX 50
#define TTL 7

struct fig {
    int index;//index in the vector of textures
    Vector2 pos;//position in window
    double time;//time of creation
};

struct fig V[NMAX];//vector of figures
int nfig=0;//number of figures

Texture2D T[NMAX];//number of textures
int ntext=0;//number of textures

void CreateTexture(char path[])
{
    Image img = LoadImage(path);
    ImageResize(&img,img.width/2,img.height/2);
    T[ntext++] = LoadTextureFromImage(img);
    UnloadImage(img);
}

void CleanTextures()
{
    for(int i=0;i<ntext;i++)
        UnloadTexture(T[i]);
}

int main(void)
{
    SetRandomSeed(time(NULL));

    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Bam Bam - Linux Logos");

    CreateTexture("resources/img/Tux.png");
    CreateTexture("resources/img/Pax_tux.png");
    CreateTexture("resources/img/Debian.png");
    CreateTexture("resources/img/Archlinux.png");
    CreateTexture("resources/img/Jellyfish.png");


    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        if(IsKeyPressed(KEY_T) && nfig<NMAX)
        {
            int idx = GetRandomValue(0,ntext-1);
            V[nfig].index = idx;
            V[nfig].pos.x = GetRandomValue(0,screenWidth-T[idx].width);
            V[nfig].pos.y = GetRandomValue(0,screenHeight-T[idx].height);
            V[nfig].time = GetTime();
            ++nfig;
        }

        // Draw
        BeginDrawing();

            ClearBackground(WHITE);

            for(int i=0;i<nfig;i++)
            {
                if(GetTime()-V[i].time <= TTL)
                    DrawTexture(T[V[i].index], V[i].pos.x, V[i].pos.y, WHITE);
                else
                {
                    if(nfig > 1)
                    {
                    struct fig x = V[i];
                    V[i] = V[nfig-1];
                    V[nfig-1] = x;
                    }
                    --nfig;
                }
            }

        EndDrawing();
    }

    CleanTextures();

    CloseWindow();

    return 0;
}
