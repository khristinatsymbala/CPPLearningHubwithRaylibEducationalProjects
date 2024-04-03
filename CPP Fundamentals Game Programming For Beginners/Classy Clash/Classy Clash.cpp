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


