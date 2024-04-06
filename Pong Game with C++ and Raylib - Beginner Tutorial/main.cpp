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



        EndDrawing();
    }
    
    CloseWindow();

}

