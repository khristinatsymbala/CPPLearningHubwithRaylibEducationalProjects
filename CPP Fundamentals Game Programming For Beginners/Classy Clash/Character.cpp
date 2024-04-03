#include "Character.h"


//called fully qualifying the function name and the two colons is known as the scope resolution
void Character::setScreenPos(int winWidth, int winHeight) {
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
        (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)
    };
}

void Character::tick(float deltaTime) {

    //= Movement logic ==============================
    Vector2 direction{};
    if (IsKeyDown(KEY_A)) direction.x -= 1;
    if (IsKeyDown(KEY_D)) direction.x += 1;
    if (IsKeyDown(KEY_W)) direction.y -= 1;
    if (IsKeyDown(KEY_S)) direction.y += 1;


    //movement checker + animation changer
    if (Vector2Length(direction) != 0.0) {

        /*
        set worldPos = worldPos + direction - ��� ���� !
        */

        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        // ������� ��������� �������� x = (�����) ? ��������1 : ��������2; 
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

    Rectangle source{ frame * (float)texture.width / 6.0f,0.f,rightleft * (float)texture.width / 6.0f,(float)texture.height };
    Rectangle dest{ screenPos.x,screenPos.y, 4.0f * (float)texture.width / 6.0f , 4.0f * (float)texture.height };

    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE); //Vector2{} - �� ���� �� ������������� ���� �� ������
}