// Classy Clash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>


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

    Enemy goblin{ Vector2{ 800.f, 800.f }, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png") };
    

    Enemy slime{Vector2{ 500.f, 300.f }, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy* enemies[]{
        &goblin,
        &slime
    };

    for (auto enemy:enemies)
    {
        enemy->setTarget(&knight);
    }
    

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

        //health display
        if (!knight.getAlive()) {//not alive
            DrawText("Game over", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else {//alive
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
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

        
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        
        //Collition weapon
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(goblin.getCollitionRec(), knight.getWeaponCollition())) {
                    enemy->setAlive(false);
                }
            }
        }
       

        //==End Drawing================================================================================================ End Drawing =======================
        EndDrawing();

    }
    UnloadTexture(map);
    
    CloseWindow();
}


