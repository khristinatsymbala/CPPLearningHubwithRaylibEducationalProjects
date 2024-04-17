#pragma once
#include "raylib.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter
{
public:
	Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
	~Enemy();

   

    //tick function - take care of things that happend every frame
    virtual void tick(float deltaTime) override;

private:
   
};

