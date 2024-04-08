#include <raylib.h>
#include <iostream>

int main(){

    Color darkBlue = {44, 44, 127, 255};


    InitWindow(300, 600, "Tetris Game");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkBlue);

        EndDrawing();
    }
    

}