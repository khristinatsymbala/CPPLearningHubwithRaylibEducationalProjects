#include "Ball.h"

void Ball::Draw()
{
     DrawCircle(x, y, radius, WHITE);
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

    if (x + radius >= GetScreenWidth() || x - radius <= 0)
    {
        speedX *= -1;
    }
    
    
}

void Ball::SetterSpeedX(int sX)
{
    speedX = sX;
}

void Ball::SetterSpeedY(int sY)
{
    speedY = sY;
}

Ball::Ball(/* args */)
{
}

Ball::~Ball()
{
}