#include "Character.h"



//called fully qualifying the function name and the two colons is known as the scope resolution


void Character::tick(float deltaTime) {

    if (!getAlive()) return;

    //= Movement logic ==============================

    if (IsKeyDown(KEY_A)) velocity.x -= 1;
    if (IsKeyDown(KEY_D)) velocity.x += 1;
    if (IsKeyDown(KEY_W)) velocity.y -= 1;
    if (IsKeyDown(KEY_S)) velocity.y += 1;
    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightleft > 0.f) {
        origin = { 0.f, weapon.height * scale };
        offset = { 35.f, 55.f };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
        

        weaponCollitionRec = { getScreenPos().x + offset.x ,
            getScreenPos().y + offset.y - weapon.height* scale,
            weapon.width  * scale,
            weapon.height * scale
        };
    }
    else {
        origin = { weapon.width * scale, weapon.height * scale };
        offset = { 25.f, 55.f };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;

        weaponCollitionRec = { getScreenPos().x + offset.x - weapon.width * scale ,
           getScreenPos().y + offset.y - weapon.height * scale,
           weapon.width * scale,
           weapon.height * scale
        };
    }

    //draw the sword
    Rectangle source{ 0.f, 0.f, static_cast<float>(weapon.width) * rightleft, static_cast<float>(weapon.height) };
    Rectangle dest{ getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale };
    DrawTexturePro(weapon, source, dest, origin,rotation,WHITE);

    DrawRectangleLines(
        weaponCollitionRec.x,
        weaponCollitionRec.y,
        weaponCollitionRec.width,
        weaponCollitionRec.height,
        RED);
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
   

