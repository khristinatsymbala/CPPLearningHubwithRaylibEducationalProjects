#include <raylib.h>
#include <iostream>

class Paddle
{
protected:
    void LimitMovement();
    /* data */
public:
    float x{};
    float y{};

    float widht{};
    float height{};

    int speed{};

    void Draw();
    void Update();
    
};

class CPUPaddle: public Paddle
{
private:
    /* data */
public:

    void Update(int ball_y);
    
};



