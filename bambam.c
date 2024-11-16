#include<time.h>
#include<ctype.h>
#include "raylib.h"

#define NMAX 50
#define TTL 7
#define FONT_SIZE 100

const int screenWidth = 1000;
const int screenHeight = 600;

Color palette[]={
    LIGHTGRAY  ,
    GRAY       ,
    DARKGRAY   ,
    YELLOW     ,
    GOLD       ,
    ORANGE     ,
    PINK       ,
    RED        ,
    MAROON     ,
    GREEN      ,
    LIME       ,
    DARKGREEN  ,
    SKYBLUE    ,
    BLUE       ,
    DARKBLUE   ,
    PURPLE     ,
    VIOLET     ,
    DARKPURPLE ,
    BEIGE      ,
    BROWN      ,
    DARKBROWN  ,
    BLACK      ,
    MAGENTA    ,
    RAYWHITE   };

const int ncolors = sizeof(palette)/sizeof(Color);

typedef enum {
	SYM, IMG
} FIG_TYPE;

struct fig {
    FIG_TYPE type;
    int index;//index in the vector of textures or -1 for symbols
    int key;//symbol to draw or -1
    int color;//index in the vector of colors or -1
    Vector2 pos;//position in the window
    double time;//time of creation
};

struct fig V[NMAX];//vector of figures
int nfig=0;//number of figures

Texture2D T[NMAX];//number of textures
int ntext=0;//number of textures

Sound S[NMAX];//vector of sounds
int nsnd=0;//number of sounds

///////////////////////////////////////////////////////////////////////////
void CreateTexture(char path[])
{
    Image img = LoadImage(path);
    ImageResize(&img,img.width/2,img.height/2);
    T[ntext++] = LoadTextureFromImage(img);
    UnloadImage(img);
}

void CreateTextures()
{
    CreateTexture("resources/img/Tux.png");
    CreateTexture("resources/img/Pax_tux.png");
    CreateTexture("resources/img/Debian.png");
    CreateTexture("resources/img/Archlinux.png");
    CreateTexture("resources/img/Jellyfish.png");
}

void CleanTextures()
{
    for(int i=0;i<ntext;i++)
        UnloadTexture(T[i]);
}

void CreateSound(char path[])
{
    S[nsnd++] = LoadSound(path);
}

void CreateSounds()
{
    CreateSound("resources/sound/Boing.mp3");
    CreateSound("resources/sound/Cowbell.mp3");
    CreateSound("resources/sound/Siren.mp3");
    CreateSound("resources/sound/Ding.mp3");
    CreateSound("resources/sound/Trombone.mp3");
}

void CleanSounds()
{
    for(int i=0;i<nsnd;i++)
        UnloadSound(S[i]);
}

void HandleKeys()
{
    int key;
    while(key=GetKeyPressed())
    {

        PlaySound(S[GetRandomValue(0,nsnd-1)]);

        if(nfig < NMAX)
        switch(key)
        {
            case KEY_APOSTROPHE:
            case KEY_COMMA:
            case KEY_MINUS:
            case KEY_PERIOD:
            case KEY_SLASH:
            case KEY_ZERO:
            case KEY_ONE:
            case KEY_TWO:
            case KEY_THREE:
            case KEY_FOUR:
            case KEY_FIVE:
            case KEY_SIX:
            case KEY_SEVEN:
            case KEY_EIGHT:
            case KEY_NINE:
            case KEY_SEMICOLON:
            case KEY_EQUAL:
            case KEY_A:
            case KEY_B:
            case KEY_C:
            case KEY_D:
            case KEY_E:
            case KEY_F:
            case KEY_G:
            case KEY_H:
            case KEY_I:
            case KEY_J:
            case KEY_K:
            case KEY_L:
            case KEY_M:
            case KEY_N:
            case KEY_O:
            case KEY_P:
            case KEY_Q:
            case KEY_R:
            case KEY_S:
            case KEY_T:
            case KEY_U:
            case KEY_V:
            case KEY_W:
            case KEY_X:
            case KEY_Y:
            case KEY_Z:
            case KEY_LEFT_BRACKET:
            case KEY_BACKSLASH:
            case KEY_RIGHT_BRACKET:
            case KEY_GRAVE:
                V[nfig].type = SYM;
                V[nfig].index = -1;
                V[nfig].key = (GetRandomValue(0,1)==0 ? key : tolower(key));
                V[nfig].pos.x = GetRandomValue(0,screenWidth-FONT_SIZE);
                V[nfig].pos.y = GetRandomValue(0,screenHeight-FONT_SIZE);
                V[nfig].color = GetRandomValue(0,ncolors-1);
                V[nfig].time = GetTime();
                ++nfig;
                break;

            default:
                int idx = GetRandomValue(0,ntext-1);
                V[nfig].type = IMG;
                V[nfig].key = -1;
                V[nfig].index = idx;
                V[nfig].pos.x = GetRandomValue(0,screenWidth-T[idx].width);
                V[nfig].pos.y = GetRandomValue(0,screenHeight-T[idx].height);
                V[nfig].color = -1;
                V[nfig].time = GetTime();
                ++nfig;
                break;
        }
    }
}

void Draw()
{
    char symbol[2]="1";

    for(int i=0;i<nfig;i++)
    {
        if(GetTime()-V[i].time <= TTL)
        {
            if(V[i].type == IMG)
                DrawTexture(T[V[i].index], V[i].pos.x, V[i].pos.y, WHITE);
            else
            {
                symbol[0]=V[i].key;
                DrawText(symbol,V[i].pos.x,V[i].pos.y,FONT_SIZE,palette[V[i].color]);
            }
        }
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
}

int main(void)
{
    SetRandomSeed(time(NULL));

    InitWindow(screenWidth, screenHeight, "Bam Bam - Linux Logos");
    InitAudioDevice();

    CreateTextures();
    CreateSounds();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        HandleKeys();

        // Draw
        BeginDrawing();

            ClearBackground(WHITE);
            Draw();

        EndDrawing();
    }

    CleanTextures();
    CleanSounds();

    CloseWindow();

    return 0;
}
