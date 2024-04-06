#include <raylib.h>
#include <iostream>
#include "Ball.h"


Ball ball;


int main(){


//===Variables====================================
    const int windowWidth{1280};
    const int windowHeight{800};

//=== ball ====================================
    ball.radius = 20;
    ball.x = windowWidth/2;
    ball.y = windowHeight/2;

    ball.SetterSpeedX(7);
    ball.SetterSpeedY(7);

    
//window ========================================
    
    InitWindow(windowWidth,windowHeight,"Pong Game!");

//Game loop ======================================
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();

        //Updating===============================
        ball.Update();

        //Drawing=================================
        ClearBackground(BLACK);
        
        DrawLine(windowWidth/2,0,windowWidth/2,windowHeight,WHITE);

       ball.Draw();


        DrawRectangle(10, windowHeight/2 - 60, 30, 120, WHITE);
        DrawRectangle(windowWidth - 35, windowHeight/2 - 60, 30, 120, WHITE);


        EndDrawing();
    }
    
    CloseWindow();

}

