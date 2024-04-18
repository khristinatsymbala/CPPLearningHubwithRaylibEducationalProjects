#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

	width = texture.width / maxFrame;
	height = texture.height;
    speed = 3.5f;
}

Enemy::~Enemy()
{
}

void Enemy::tick(float deltaTime)
{
    //go to target 
    Vector2 toTarget = Vector2Subtract(target->getScrenPos(), screenPos);
    //nirmalize to Target
    toTarget = Vector2Normalize(toTarget);
    //multiply toTarget by speed
    toTarget = Vector2Scale(toTarget, speed);
    //move the Enemy
    worldPos = Vector2Add(worldPos,toTarget);

    screenPos =  Vector2Subtract(worldPos,target->getWorldPos());
    BaseCharacter::tick(deltaTime);
    
}

void Enemy::setTarget(Character*character)
{
    target = character;
}


