#include "Character.h"


//called fully qualifying the function name and the two colons is known as the scope resolution
void Character::setScreenPos(int winWidth, int winHeight) {
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * width),
        (float)winHeight / 2.0f - 4.0f * (0.5f * height)
    };
}

void Character::tick(float deltaTime) {

    worldPosLastFrame = worldPos;

    //= Movement logic ==============================
    Vector2 direction{};
    if (IsKeyDown(KEY_A)) direction.x -= 1;
    if (IsKeyDown(KEY_D)) direction.x += 1;
    if (IsKeyDown(KEY_W)) direction.y -= 1;
    if (IsKeyDown(KEY_S)) direction.y += 1;

    
    //movement checker + animation changer
    if (Vector2Length(direction) != 0.0) {

        /*
        set worldPos = worldPos + direction - рух мапи !
        */
        
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        // Умовний тернарний оператор x = (умова) ? значення1 : значення2; 
        direction.x < 0.f ? rightleft = -1.f : rightleft = 1.f;
        texture = run;
        
    }
    else {
        texture = idle;
    }

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
    Rectangle dest{ screenPos.x,screenPos.y, 4.0f * width , 4.0f * height };

    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE); //Vector2{} - то саме що ініційовувати його за межами
}

Character::Character()
{
    width = texture.width / maxFrame;
    height = texture.height;
}

void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}
