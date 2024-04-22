#include "Block.h"

Block::Block(/* args */)
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
}

Block::~Block()
{
}

void Block::Draw()
{
}