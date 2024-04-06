#include "Paddle.h"

void Paddle::Draw()
{
    DrawRectangle(x, y, widht, height, WHITE);
}

void Paddle::Update()
{
    if (IsKeyDown(KEY_UP))
    {
        y -= speed;
    }

    if(IsKeyDown(KEY_DOWN)){
        y += speed;
    }

    if (y  <= 0)
    {
        y = 0;
    }

    if (y + height >= GetScreenHeight())
    {
        y = GetScreenHeight() - height;
    }
    
    
    
}

void CPUPaddle::Update(int ball_y)
{
    if (y + height/2 > ball_y)
    {
        y -= speed;
    }

    if (y + height/2 <= ball_y)
    {
        y += speed;
    }
    
}
