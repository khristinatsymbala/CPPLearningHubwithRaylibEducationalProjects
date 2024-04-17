#include "Enemy.h"


Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

	width = texture.width / maxFrame;
	height = texture.height;
}

Enemy::~Enemy()
{
}

void Enemy::tick(float deltaTime)
{
	worldPosLastFrame = worldPos;
    //update animation frame 
    runningTime += deltaTime;

    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrame) frame = 0;

    }

    //draw a character

    Rectangle source{ frame * width,0.f,rightleft * width,height };
    Rectangle dest{ screenPos.x,screenPos.y, scale * width , 4.0f * height };

    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}


