#include "helper.h"

sf::Vector2f get_cell_position(int row,int column)
{
    return sf::Vector2f(
        setting::cell_offset + column * ( setting::cell_size + setting::line_space),
        setting::cell_offset + row * ( setting::cell_size + setting::line_space));
}

string get_xo_path(Id id)
{
    string path = "resources/images/";
    if (id == PW) path += "whitePawn";
    if (id == PB) path += "blackPawn";
    if (id == BW) path += "whiteBishop";
    if (id == BB) path += "blackBishop";
    if (id == NW) path += "whiteKnight";
    if (id == NB) path += "blackKnight";
    if (id == RW) path += "whiteRook";
    if (id == RB) path += "blackRook";
    if (id == QW) path += "whiteQueen";
    if (id == QB) path += "blackQueen";
    if (id == KW) path += "whiteKing";
    if (id == KB) path += "blackKing";
    // path += (id == PW ? "whiteQueen" : "blackRook");
    return path + ".png";
}

int get_cell_index(int x)
{
    x -= setting::cell_offset;
    if (x<0)
        return -1;
    int cell_plus_space = setting::cell_size + setting::line_space;
    int index = x / cell_plus_space;
    if (index > 7 || x > index * cell_plus_space + setting::cell_size)
        return -1;
    return index;
}

string get_name_of_id(Id id)
{
    return id == PW ? "white" : "black";
}