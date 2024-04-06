#include "Ball.h"

void Ball::Draw()
{
     DrawCircle(x, y, radius, WHITE);
}

void Ball::Update()
{
    x += speedX;
    y += speedY;
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