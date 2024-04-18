// Classy Clash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"


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
    const float mapScale{ 4.0f };


    // Declare an object of class geeks 
    Character knight{ windowWidth, windowHeight };


    Prop props[2]{
    Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
    Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    Enemy goblin( Vector2{ 300.f, 300.f }, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png"));
    goblin.setTarget(&knight);


    SetTargetFPS(60);
//== Main game loop ======================================================================================================= Main game loop ======================
    while (!WindowShouldClose())
    {

        //== Start Drawing ================================================================================================ Start Drawing =======================
        BeginDrawing();
        ClearBackground(WHITE);
        
        //moving map in opposite side
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        //draw a background
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        //range base array
        //Draw the props
        for (auto prop : props) {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());
       
        //map restrictions - check map dounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        //Collition checker
        for (auto prop : props) {
            if (CheckCollisionRecs(knight.getCollitionRec(), prop.getCollitionRec(knight.getWorldPos()))) {
                knight.undoMovement();
            }
        }

        goblin.tick(GetFrameTime());
        
        //Collition weapon
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionRecs(goblin.getCollitionRec(), knight.getWeaponCollition())) {
                goblin.setAlive(false);
           }

        }
       

        //==End Drawing================================================================================================ End Drawing =======================
        EndDrawing();

    }
    UnloadTexture(map);
    
    CloseWindow();
}


