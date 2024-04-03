// Classy Clash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <raylib.h>
#include <raymath.h>
//== Classes ================================================================================================================= Classes ======================
class Character {
public:
    //Getter to world position
    Vector2 getWorlsPos() { return worldPos; }
    
    void setScreenPos(int winWidth, int winHeight);

    //tick function - take care of things that happend every frame
    void tick(float deltaTime);

private:
    
    Texture2D texture{ LoadTexture("characters/knight_idle_spritesheet.png") };
    Texture2D idle{ LoadTexture("characters/knight_idle_spritesheet.png") };
    Texture2D run{ LoadTexture("characters/knight_run_spritesheet.png") };

    Vector2 screenPos;
    Vector2 worldPos;

    //1 = right; -1 = left - character direction
    float rightleft{ 1.f };

    //animation variables
    float runningTime{};
    int frame{};
    const int maxFrame{ 6 };//base spritesheet
    const float updateTime{ 1.f / 12.f };
    const float speed{ 4.f };
};

//called fully qualifying the function name and the two colons is known as the scope resolution
void Character::setScreenPos(int winWidth, int winHeight) {
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
        (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)
    };
}

void Character::tick(float deltaTime) {
    Vector2 direction{};
    if (IsKeyDown(KEY_A)) direction.x -= 1;
    if (IsKeyDown(KEY_D)) direction.x += 1;
    if (IsKeyDown(KEY_W)) direction.y -= 1;
    if (IsKeyDown(KEY_S)) direction.y += 1;


    //movement checker + animation changer
    if (Vector2Length(direction) != 0.0) {

        /*
        set worldPos = worldPos + direction - рух мапи !
        */

        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        // Умовний тернарний оператор x = (умова) ? значення1 : значення2; 
        direction.x < 0.f ? rightleft = -1.f : rightleft = 1.f;
        texture = run;
    }
    else {
        texture = idle;
    }

    //update animation frame 
    runningTime += deltaTime;

    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrame) frame = 0;

    }
}

int main()
{
// == Initialization window ===============================================================================================Initialization window ============ 
    const int windowWidth = 384;
    const int windowHeight = 384;

    InitWindow(windowWidth, windowHeight, "Classy clash");


//== Textures ====================================================================================================================Textures====================
    //map
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{ 0.0, 0.0 };
    float speed{4.0};

    //knight 
    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");


    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
        (float)windowWidth / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),
        (float)windowHeight / 2.0f - 4.0f * (0.5f * (float)knight.height)
        // f вкінці означає конвертування в флоат, (float) аналогічно тільки на початку
    };

    //1 = right; -1 = left - character direction
    float rightleft{ 1.f };
    
    //animation variables
    float runningTime{};
    int frame{};
    const int maxFrame{6};//base spritesheet
    const float updateTime{1.f/12.f};

    SetTargetFPS(60);
//== Main game loop ======================================================================================================= Main game loop ======================
    while (!WindowShouldClose())
    {

        //== Start Drawing ================================================================================================ Start Drawing =======================
        BeginDrawing();
        ClearBackground(WHITE);
        
       

        //= Movement logic ==============================

        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1;
        if (IsKeyDown(KEY_D)) direction.x += 1;
        if (IsKeyDown(KEY_W)) direction.y -= 1;
        if (IsKeyDown(KEY_S)) direction.y += 1;
        
       
        //movement checker + animation changer
        if (Vector2Length(direction) != 0.0) {

            /*
            To normalize movement along the diagonal, it is imperative to define either this vector normalized or a singular vector. 
           
            set mapPos = mapPos - direction - рух мапи !

            Vector2Scale(Vector2Normalize(direction),speed) - це врегулювання швидкості руху, ми множимо швидкість на сам мувмент
            */
            
            mapPos = Vector2Subtract(mapPos,Vector2Scale(Vector2Normalize(direction),speed));
            // Умовний тернарний оператор x = (умова) ? значення1 : значення2; 
            direction.x < 0.f ? rightleft = -1.f : rightleft = 1.f;
            knight = knight_run;
        }
        else {
            knight = knight_idle;
        }

        //draw a background
        DrawTextureEx(map, mapPos, 0.0, 4, WHITE);

        //draw a character
        //не забуваєм що для позиції треба створювати додаткові макети ректанглу, для майбутнього DrawTexturePro 
        //це Rectangle source - як первинна позиція,Rectangle dest-для майбутнього переміщення


        Rectangle source{ frame * (float)knight.width / 6.0f,0.f,rightleft * (float)knight.width / 6.0f,(float)knight.height };
        Rectangle dest{ knightPos.x,knightPos.y, 4.0f * (float)knight.width / 6.0f , 4.0f * (float)knight.height };

        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE); //Vector2{} - то саме що ініційовувати його за межами

        //update animation frame - logic dapper dasher
        runningTime += GetFrameTime();

        if (runningTime>=updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrame) frame = 0;
         
        }



        //==End Drawing================================================================================================ End Drawing =======================
        EndDrawing();

    }
    UnloadTexture(map);
    UnloadTexture(knight);
    CloseWindow();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
