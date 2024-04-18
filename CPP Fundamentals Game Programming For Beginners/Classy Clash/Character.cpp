#include "Character.h"



//called fully qualifying the function name and the two colons is known as the scope resolution


void Character::tick(float deltaTime) {


    //= Movement logic ==============================

    if (IsKeyDown(KEY_A)) velocity.x -= 1;
    if (IsKeyDown(KEY_D)) velocity.x += 1;
    if (IsKeyDown(KEY_W)) velocity.y -= 1;
    if (IsKeyDown(KEY_S)) velocity.y += 1;
    BaseCharacter::tick(deltaTime);
}


Character::Character(int winWidth, int winHeight)
    :windowWidth(winWidth),windowHeight(winHeight)
{
        width = texture.width / maxFrame;
        height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2{
            static_cast<float> (windowWidth) / 2.0f - scale * (0.5f * width),
            static_cast<float> (windowHeight) / 2.0f - scale * (0.5f * height)
    };
}
   

