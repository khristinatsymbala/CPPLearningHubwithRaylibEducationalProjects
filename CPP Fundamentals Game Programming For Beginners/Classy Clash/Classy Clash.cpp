// Classy Clash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "Character.h"


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

        knight.tick(GetFrameTime());
       
        //map restrictions - check map dounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }



        //==End Drawing================================================================================================ End Drawing =======================
        EndDrawing();

    }
    UnloadTexture(map);
    
    CloseWindow();
}


