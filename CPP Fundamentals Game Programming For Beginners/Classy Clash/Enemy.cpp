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
    if (!getAlive()) return;
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    BaseCharacter::tick(deltaTime);
    
    if (CheckCollisionRecs(target->getCollitionRec(), getCollitionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

void Enemy::setTarget(Character*character)
{
    target = character;
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());;
}


