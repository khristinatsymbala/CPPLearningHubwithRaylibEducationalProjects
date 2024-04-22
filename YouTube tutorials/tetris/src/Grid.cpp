#include "Grid.h"
#include "Colors.h"
#include <iostream>

Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int colomn = 0; colomn < numCols; colomn++)
        {
            grid[row][colomn] = 0;
        }
    }
}

void Grid::Print()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int colomn = 0; colomn < numCols; colomn++)
        {
            std::cout << grid[row][colomn] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int colomn = 0; colomn < numCols; colomn++)
        {
            int cellValue = grid[row][colomn];
            DrawRectangle(colomn * cellSize + 1, row * cellSize + 1, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}
