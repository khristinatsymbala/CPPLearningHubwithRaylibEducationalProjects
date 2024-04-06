#include <raylib.h>
#include <iostream>
#include "Ball.h"
#include "Paddle.h"


Ball ball;

Paddle player;


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
//=== paddle_player ====================================
    player.widht = 30;
    player.height = 120;

    player.x = windowWidth - player.widht - 10;
    player.y = windowHeight/2 - player.height/2;

    player.speed = 6;

//window ========================================
    
    InitWindow(windowWidth,windowHeight,"Pong Game!");

//Game loop ======================================
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();

        //Updating===============================
        ball.Update();
        player.Update();

        //Drawing=================================
        ClearBackground(BLACK); // update a window every frame

        DrawLine(windowWidth/2,0,windowWidth/2,windowHeight,WHITE);

       ball.Draw();


        DrawRectangle(10, windowHeight/2 - 60, 30, 120, WHITE);
        player.Draw();
    


        EndDrawing();
    }
    
    CloseWindow();

}

