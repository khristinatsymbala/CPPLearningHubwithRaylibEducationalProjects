#include <raylib.h>
#include <iostream>

class Ball
{
private:
    Color Yellow = Color{243, 213, 91, 255};
public:
    float x{};
    float y{};

    int radius{};

    void Draw();
    void Update();

    int speedX{};
    int speedY{};

    int player_score = 0;
    int cpu_score = 0;
    
    void ResetBall();
};


