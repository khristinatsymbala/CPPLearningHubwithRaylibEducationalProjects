#pragma once
#include "raylib.h"

class Enemy
{
public:
	Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
	~Enemy();

    Vector2 getWorldPos() { return worldPos; }

    //tick function - take care of things that happend every frame
    void tick(float deltaTime);

    void undoMovement();

    Rectangle getCollitionRec();

private:
    Texture2D texture{ LoadTexture("characters/knight_idle_spritesheet.png") };
    Texture2D idle{ LoadTexture("characters/knight_idle_spritesheet.png") };
    Texture2D run{ LoadTexture("characters/knight_run_spritesheet.png") };

    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    //1 = right; -1 = left - character direction
    float rightleft{ 1.f };

    //animation variables
    float runningTime{};
    int frame{};
    int maxFrame{ 6 };//base spritesheet
    float updateTime{ 1.f / 12.f };
    float speed{ 4.f };

    float width{};
    float height{};

    float scale{ 4.0f };

};

