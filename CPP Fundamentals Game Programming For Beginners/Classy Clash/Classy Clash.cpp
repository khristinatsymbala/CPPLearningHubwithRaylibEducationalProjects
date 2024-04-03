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

    Vector2 screenPos {};
    Vector2 worldPos{};

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

    //= Movement logic ==============================
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

    //draw a character

    Rectangle source{ frame * (float)texture.width / 6.0f,0.f,rightleft * (float)texture.width / 6.0f,(float)texture.height };
    Rectangle dest{ screenPos.x,screenPos.y, 4.0f * (float)texture.width / 6.0f , 4.0f * (float)texture.height };

    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE); //Vector2{} - то саме що ініційовувати його за межами
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

  
    
    // Declare an object of class geeks 
    Character knight;

    knight.setScreenPos(windowWidth, windowHeight);
    

    SetTargetFPS(60);
//== Main game loop ======================================================================================================= Main game loop ======================
    while (!WindowShouldClose())
    {

        //== Start Drawing ================================================================================================ Start Drawing =======================
        BeginDrawing();
        ClearBackground(WHITE);
        
        //moving map in opposite side
        mapPos = Vector2Scale(knight.getWorlsPos(), -1.f);

        //draw a background
        DrawTextureEx(map, mapPos, 0.0, 4, WHITE);

        knight.tick(GetFrameTime());
       

        


        //==End Drawing================================================================================================ End Drawing =======================
        EndDrawing();

    }
    UnloadTexture(map);
    
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
