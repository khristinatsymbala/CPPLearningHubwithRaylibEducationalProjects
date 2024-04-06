#include <raylib.h>
#include <iostream>
#include "Ball.h"
#include "Paddle.h"

Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};



Ball ball;

Paddle player;
CPUPaddle cpu;


int main(){
//===Variables====================================
    const int windowWidth{1280};
    const int windowHeight{800};

//=== ball ====================================
    ball.radius = 20;
    ball.x = windowWidth/2;
    ball.y = windowHeight/2;

    ball.speedX = 7;
    ball.speedY = 7;
//=== paddle_player ====================================
    player.widht = 30;
    player.height = 120;

    player.x = windowWidth - player.widht - 10;
    player.y = windowHeight/2 - player.height/2;

    player.speed = 6;

//=== cpu paddle_player ====================================

    cpu.widht = 30;
    cpu.height = 120;

    cpu.x = 10;
    cpu.y = windowHeight/2 - cpu.height/2;

    cpu.speed = 6;

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
        cpu.Update(ball.y);

        //Checking collision =====================
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, Rectangle{player.x, player.y, player.widht, player.height})){
                ball.speedX *= -1;
        }

        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.widht, cpu.height})){
                ball.speedX *= -1;
        }

        //Drawing=================================
        ClearBackground(Dark_Green); // update a window every frame
        DrawRectangle(windowWidth / 2, 0, windowWidth / 2, windowHeight, Green);
        DrawCircle(windowWidth / 2, windowHeight / 2, 150, Light_Green);

        DrawLine(windowWidth/2,0,windowWidth/2,windowHeight,WHITE);

        ball.Draw();
        cpu.Draw();
        player.Draw();
    
        DrawText(TextFormat("%i", ball.cpu_score),windowWidth/4-20,20,80,WHITE);
        DrawText(TextFormat("%i", ball.player_score),3*windowWidth/4-20,20,80,WHITE);

        EndDrawing();
    }
    
    CloseWindow();

}

