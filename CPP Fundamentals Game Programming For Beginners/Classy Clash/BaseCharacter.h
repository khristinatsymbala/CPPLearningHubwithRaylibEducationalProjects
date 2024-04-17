#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
public:
	BaseCharacter();
	~BaseCharacter();

    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    Rectangle getCollitionRec();

    virtual void tick(float deltaTime);

protected:
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

private:
    
};

#endif 