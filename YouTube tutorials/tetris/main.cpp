#include <raylib.h>
#include <iostream>
#include "Grid.h"



int main(){

    Color darkBlue = {44, 44, 127, 255};
    InitWindow(300, 600, "Tetris Game");

    SetTargetFPS(60);


    Grid grid = Grid();
    grid.Print();

    grid.grid[0][0] = 1;
    grid.grid[3][6] = 4;
    grid.grid[17][8] = 7;


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkBlue);
        grid.Draw();


        EndDrawing();
    }
    

}