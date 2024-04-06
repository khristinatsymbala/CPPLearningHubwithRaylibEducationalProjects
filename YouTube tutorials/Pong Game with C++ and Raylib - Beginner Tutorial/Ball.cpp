#include "Ball.h"

void Ball::Draw()
{
     DrawCircle(x, y, radius, Yellow);
}

void Ball::Update()
{
    x += speedX;
    y += speedY;

    //colition with screen
    if (y + radius >= GetScreenHeight() || y - radius <= 0)
    {
        speedY *= -1;
    }

    if (x + radius >= GetScreenWidth())//CPU wins
    {
        cpu_score++;
        ResetBall();
    } 
    if( x - radius <= 0)
    {
        player_score++;
        ResetBall();
    }
    
    
}

void Ball::ResetBall()
{
    x = GetScreenWidth()/2;
    y = GetScreenHeight()/2;

    int speedChoise[2] = {-1,1};

    speedX *= speedChoise[GetRandomValue(0,1)];
    speedY *= speedChoise[GetRandomValue(0,1)];
}
