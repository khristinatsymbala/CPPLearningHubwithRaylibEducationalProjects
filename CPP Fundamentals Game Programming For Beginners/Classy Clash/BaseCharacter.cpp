#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}

BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollitionRec()
{
    return Rectangle{
            getScreenPos().x,
            getScreenPos().y,
            width * scale,
            height * scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
    runningTime += deltaTime;

    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrame) frame = 0;

    }
    //movement checker + animation changer
    if (Vector2Length(velocity) != 0.0) {

      

        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        // Умовний тернарний оператор x = (умова) ? значення1 : значення2; 
        velocity.x < 0.f ? rightleft = -1.f : rightleft = 1.f;
        texture = run;

    }
    else {
        texture = idle;
    }
    velocity = {};

    //draw a character

    Rectangle source{ frame * width,0.f,rightleft * width,height };
    Rectangle dest{ getScreenPos().x,getScreenPos().y, scale * width , 4.0f * height };

    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE); //Vector2{} - то саме що ініційовувати його за межами
}

