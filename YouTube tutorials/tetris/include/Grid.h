#pragma once
#include "raylib.h"
#include <vector>

class Grid
{
private:
    int numCols{};
    int numRows{};
    int cellSize{};
public:
    Grid();
    int grid [20][10];

    void Initialize();
    void Print();
    void Draw();

    std::vector<Color> colors;
    std::vector<Color> getCellColors();
};
