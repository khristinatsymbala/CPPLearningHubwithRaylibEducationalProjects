#include <raylib.h>
#include <iostream>

int main(){


//===Variables====================================
    const int windowWidth{1280};
    const int windowHeight{800};
    
//window ========================================
    
    InitWindow(windowWidth,windowHeight,"Pong Game!");

//Game loop ======================================
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();

        //Drawing=================================
        DrawLine(windowWidth/2,0,windowWidth/2,windowHeight,WHITE);

        DrawCircle(windowWidth/2, windowHeight/2, 20, WHITE);


        DrawRectangle(10, windowHeight/2 - 60, 30, 120, WHITE);
        DrawRectangle(windowWidth - 35, windowHeight/2 - 60, 30, 120, WHITE);


        EndDrawing();
    }
    
    CloseWindow();

}

