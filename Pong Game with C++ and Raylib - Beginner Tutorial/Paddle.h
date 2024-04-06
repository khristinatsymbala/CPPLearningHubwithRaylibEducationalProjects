#include <raylib.h>
#include <iostream>

class Paddle
{
private:
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


