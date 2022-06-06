#ifndef CELL_H
#define CELL_H

#include "vector"
#include "data.h"
#include "xo.h"

class Cell
{
public:
    sf::CircleShape circle;
    sf::RectangleShape rect;
    sf::RectangleShape rect2;
    CellStatus cell_status = EMPTY;
    XO* xo;
};

typedef typename std::vector<std::vector<Cell>> Cells;


#endif