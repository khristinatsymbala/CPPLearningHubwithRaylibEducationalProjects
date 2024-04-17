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
