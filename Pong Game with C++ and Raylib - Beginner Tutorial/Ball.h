#include <raylib.h>
#include <iostream>

class Ball
{
private:
    int speedX{};
    int speedY{};
public:
    float x{};
    float y{};

    int radius{};

    void Draw();
    void Update();

// Setter =================
    void SetterSpeedX(int sX);
    void SetterSpeedY(int sY);

//Getter ===================
    int getSX(){return speedX;}
    int getSY(){return speedY;}

    
    Ball(/* args */);
    ~Ball();
};


