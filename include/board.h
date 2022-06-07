#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <SFML/Graphics.hpp>
#include "user.h"
#include "data.h"
#include "cell.h"
#include "setting.h"
#include "helper.h"

class Board
{
public:

    enum WhichTurn
    {
        MOHRESELECT,
        PLACESELECT
    };
    WhichTurn turnForWhat = MOHRESELECT;
    Board(sf::RenderWindow* _window);
    sf::RenderWindow* window;
    Cells cells;
    User* pw;
    User* pb;
    User* kb;
    User* kw;
    User* bb;
    User* bw;
    User* nb;
    User* nw;
    User* rb;
    User* rw;
    User* qb;
    User* qw;
    User* curr_user;
    sf::Font font;
    bool end;
    sf::Text status_text;
    void init();
    void draw();
    void run(string myString[8][8]);
    void mouse_clicked(const sf::Vector2i& position, string myString[8][8]);
    void cell_empty_clicked(int row, int column);
    void occupeted_cell_clicked(int row, int column);
    void put_xo_in_cell(int row, int column);
    void check_end();
    void update_status_text();
    void draw2(int x,int y);
    bool pawnValid(int x, int y, int desI, int desJ, string tb[8][8], string MohreName);
    bool knightValid(int x, int y, int desI, int desJ, string tb[8][8], string MohreName);
    bool bishopValid(int x, int y, int desI, int desJ, string tb[8][8], string MohreName);
    bool queenValid(int x, int y, int desI, int desJ, string tb[8][8], string MohreName);
    bool rookValid(int x, int y, int desI, int desJ, string tb[8][8], string MohreName);
};

#endif