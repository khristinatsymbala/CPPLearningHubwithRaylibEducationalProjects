#include "BaseCharacter.h"

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
            screenPos.x,
            screenPos.y,
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

    //draw a character

    Rectangle source{ frame * width,0.f,rightleft * width,height };
    Rectangle dest{ screenPos.x,screenPos.y, scale * width , 4.0f * height };

    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE); //Vector2{} - то саме що ініційовувати його за межами
}
}
