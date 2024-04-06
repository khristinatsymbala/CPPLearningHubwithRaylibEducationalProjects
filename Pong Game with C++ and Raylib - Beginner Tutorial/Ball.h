#include <raylib.h>
#include <iostream>

class Ball
{
private:
    
public:
    float x{};
    float y{};

    int radius{};

    void Draw();
    void Update();

    int speedX{};
    int speedY{};


    
    Ball(/* args */);
    ~Ball();
};


