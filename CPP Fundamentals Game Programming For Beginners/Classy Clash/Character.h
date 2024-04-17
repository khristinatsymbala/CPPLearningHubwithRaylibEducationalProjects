#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:

    //tick function - take care of things that happend every frame
    void tick(float deltaTime);
    
    Character(int winWidth, int winHeight);
    
private:

};