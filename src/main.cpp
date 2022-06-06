#include "board.h"
#include <iostream>
// #include "piadeSazi.cpp"
using namespace sf;

int main()
{
    int a;
    cin >> a;
    string myString[8][8];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            cin >> myString[i][j];
    }
    RenderWindow window(VideoMode(1080, 900), "Tic Tac Toe", Style::Titlebar | Style::Close);
    Board board(&window);
    board.run(myString);
}