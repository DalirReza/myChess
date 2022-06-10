#include "board.h"
#include "iostream"

Board::Board(sf::RenderWindow* _window) : window(_window)
{
    this->pw = new User(PW);
    this->pb = new User(PB);
    this->kw = new User(KW);
    this->kb = new User(KB);
    this->nw = new User(NW);
    this->nb = new User(NB);
    this->bw = new User(BW);
    this->bb = new User(BB);
    this->qw = new User(QW);
    this->qb = new User(QB);
    this->rw = new User(RW);
    this->rb = new User(RB);
    this->window->setFramerateLimit(60);
}

void Board::init()
{
    sf::Color lightBlue(205,219,226);
    sf::Color darkBlue(124,156,177);
    end = false;
    this->cells.resize(8);
    for (int row = 0; row < 8; row++)
    {
        this->cells[row].resize(8);
        for (int column = 0; column < 8; column++)
        {
            this->cells[row][column].rect.setSize(sf::Vector2f(setting::cell_size, setting::cell_size));
            if ((row+column)%2 == 0)
                this->cells[row][column].rect.setFillColor(lightBlue);
            else this->cells[row][column].rect.setFillColor(darkBlue);
            this->cells[row][column].rect.setPosition(get_cell_position(row, column));
        }
    }
    // this->curr_user = this->user_x;
    font.loadFromFile("resources/fonts/roboto.ttf");
    status_text.setFont(font);
    status_text.setCharacterSize(30);
    status_text.setStyle(sf::Text::Regular);
    status_text.setFillColor(sf::Color::Black);
    status_text.setPosition(890.f, 80.f);
    this->update_status_text();
}

void Board::draw()
{
    sf::RenderTexture rendertexture;
    rendertexture.clear();
    rendertexture.display();
    // rendertexture.draw();
    const sf::Texture& texture = rendertexture.getTexture();
    sf::Sprite sprite(texture);
    for (int row = 0; row < 8; row++)
        for (int column = 0; column < 8; column++)
        {
            this->window->draw(this->cells[row][column].rect);
            if (this->cells[row][column].cell_status == OCCUPIED)
            {
                // cout << row << " " << column << " " << this->cells[row][column].cell_status << endl;
                this->window->draw(this->cells[row][column].xo->sprite);
            }
        }
    this->window->draw(this->status_text);
}

bool Board::knightValid(int x, int y, int desI, int desJ, string tb[8][8], string MohreName)
{
    if (desI>=0 and desI<8 and desJ>=0 and desJ<8)
        {
            if (((desI==x+1 and desJ==y+2)or(desI==x+1 and desJ==y-2)or(desI==x-1 and desJ==y+2)or(desI==x-1 and desJ==y-2)
            or(desI==x+2 and desJ==y+1)or(desI==x+2 and desJ==y-1)or(desI==x-2 and desJ==y+1)or(desI==x-2 and desJ==y-1))
            and tb[desI][desJ][1] != MohreName[1])
                return true;
        }
    return false;
}

bool Board::bishopValid(int x, int y, int desI, int desJ, string tb[8][8], string MohreName)
{
    if (desI>=0 and desJ>=0 and desI<8 and desJ<8) 
        {
            if((tb[desI][desJ] == "--" and (desI-x == desJ-y or desI+desJ == x+y)) or (tb[desI][desJ] != "--" and tb[desI][desJ][1] != MohreName[1] and (x+desJ == y+desI or x+desI == y+desJ)))
            {
                int myMin = min(x, desI), myMax = max(x, desI), myMinJ = min(y, desJ);
                for (int i = 1; i < myMax - myMin; i++)
                {
                    if ((myMin == x and myMinJ == y) or (myMin == desI and myMinJ == desJ))
                    {
                        if(tb[myMin+i][myMinJ+i] != "--")
                            return false;
                    }
                    else if (tb[myMax-i][myMinJ+i] != "--")
                        return false;
                }
                return true;
            }
        }
    return false;
}

bool Board::queenValid(int x, int y, int desI, int desJ, string tb[8][8], string MohreName)
{
    if (desI>=0 and desJ>=0 and desI<8 and desJ<8) 
        {
            if((tb[desI][desJ] == "--" and (desI-x == desJ-y or desI+desJ == x+y)) or (tb[desI][desJ] != "--" and tb[desI][desJ][1] != MohreName[1] and (x+desJ == y+desI or x+desI == y+desJ)))
            {
                int myMin = min(x, desI), myMax = max(x, desI), myMinJ = min(y, desJ);
                for (int i = 1; i < myMax - myMin; i++)
                {
                    if ((myMin == x and myMinJ == y) or (myMin == desI and myMinJ == desJ))
                    {
                        if(tb[myMin+i][myMinJ+i] != "--")
                            return false;
                    }
                    else if (tb[myMax-i][myMinJ+i] != "--")
                        return false;
                }
                return true;
            }
            else if ((tb[desI][desJ] == "--" or tb[desI][desJ][1] != MohreName[1]) and (desI == x or desJ == y))
            {
                if (desI == x)
                {
                    int myMaxJ = max(desJ, y), myMinJ = min(desJ, y);
                    for (int i = myMinJ + 1; i < myMaxJ; i++)
                    {
                        if (tb[x][i] != "--")
                            return false;
                    }
                    return true;
                }
                else
                {
                    int myMax = max(desI, x), myMin = min(desI, x);
                    for (int i = myMin + 1; i < myMax; i++)
                    {
                        if (tb[i][y] != "--")
                            return false;
                    }
                    return true;
                }
            }
        }
    return false;
}

bool Board::rookValid(int x, int y, int desI, int desJ, string tb[8][8], string MohreName)
{
    if (desI>=0 and desI<8 and desJ>=0 and desJ<8)
        {
            if ((tb[desI][desJ] == "--" or tb[desI][desJ][1] != MohreName[1]) and (desI == x or desJ == y))
            {
                if (desI == x)
                {
                    int myMaxJ = max(desJ, y), myMinJ = min(desJ, y);
                    for (int i = myMinJ + 1; i < myMaxJ; i++)
                    {
                        if (tb[x][i] != "--")
                            return false;
                    }
                    return true;
                }
                else
                {
                    int myMax = max(desI, x), myMin = min(desI, x);
                    for (int i = myMin + 1; i < myMax; i++)
                    {
                        if (tb[i][y] != "--")
                            return false;
                    }
                    return true;
                }
            }
        }
    return false;
}

bool Board::pawnValid(int x, int y, int desI, int desJ, string tb[8][8], string MohreName)
{
    if((desI!=x or desJ!=y) and (tb[desI][desJ]=="--") and (desI<8 and desJ<8 and desI>=0 and desJ>=0))
    {
        if(MohreName[1] == 'B')
        {
            if (x == 1 and (desI == 2 or desI == 3) and desJ == y)
            {
                return true;
            }
            else if (x != 1 and desI == x + 1 and desJ == y)
                return true;
        }
        else 
        {
            if (x == 6 and (desI == 5 or desI == 4) and desJ == y)
                return true;
            else if (x != 6 and desI == x - 1 and desJ == y)
                return true;
        }
    }
    else if((desI != x or desJ != y) and (tb[desI][desJ][1] == 'B') and MohreName[1] == 'W' and
    (desI == x-1 ) and (desJ == y+1 or desJ == y-1))
        return true;
    else if((desI != x or desJ != y) and (tb[desI][desJ][1] == 'W') and MohreName[1] == 'B' and
    (desI == x+1) and (desJ == y+1 or desJ == y-1))
        return true;
    return false;
}



void Board::draw2(int x, int y)
{
    sf::Color lightGreen(144, 238, 144);
    this->cells[x][y].rect.setSize(sf::Vector2f(setting::cell_size, setting::cell_size));
    this->window->draw(this->cells[x][y].rect2);
    this->cells[x][y].rect.setFillColor(lightGreen);
}

void Board::run(string myString[8][8])
{
    window->clear();
    this->init();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (myString[i][j] == "PB") {this->curr_user->id = PB; put_xo_in_cell(i, j);}
            if (myString[i][j] == "PW") {this->curr_user->id = PW; put_xo_in_cell(i, j);}
            if (myString[i][j] == "NW") {this->curr_user->id = NW; put_xo_in_cell(i, j);}
            if (myString[i][j] == "NB") {this->curr_user->id = NB; put_xo_in_cell(i, j);}
            if (myString[i][j] == "BW") {this->curr_user->id = BW; put_xo_in_cell(i, j);}
            if (myString[i][j] == "BB") {this->curr_user->id = BB; put_xo_in_cell(i, j);}
            if (myString[i][j] == "RW") {this->curr_user->id = RW; put_xo_in_cell(i, j);}
            if (myString[i][j] == "RB") {this->curr_user->id = RB; put_xo_in_cell(i, j);}
            if (myString[i][j] == "QW") {this->curr_user->id = QW; put_xo_in_cell(i, j);}
            if (myString[i][j] == "QB") {this->curr_user->id = QB; put_xo_in_cell(i, j);}
            if (myString[i][j] == "KW") {this->curr_user->id = KW; put_xo_in_cell(i, j);}
            if (myString[i][j] == "KB") {this->curr_user->id = KB; put_xo_in_cell(i, j);}
        }
    }

    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {

    //     }
    // }
    // this->window->display();
    while (this->window->isOpen()) {
        sf::Event event;
        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->window->close();
            }
            if (!this->end && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->mouse_clicked(sf::Mouse::getPosition(*(this->window)), myString);
            }
        }
        this->window->clear(sf::Color(150, 150, 150));
        this->update_status_text();
        this->draw();
        this->window->display();
    }
}

void Board::mouse_clicked(const sf::Vector2i& position, string myString[8][8])
{
    int row = get_cell_index(position.y), column = get_cell_index(position.x);
    if (turnForWhat == MOHRESELECT)
    {
        if (this->cells[row][column].cell_status == OCCUPIED)
        {
            this->curr_user->x = row;
            this->curr_user->y = column;
            turnForWhat = PLACESELECT;
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (myString[row][column][0] == 'P' and pawnValid(row, column, i, j, myString, myString[row][column]))
                    {
                        draw2(i, j);
                        this->curr_user->id = PW;
                    }
                    else if (myString[row][column][0] == 'N' and knightValid(row, column, i, j, myString, myString[row][column]))
                    {
                        draw2(i, j);
                        this->curr_user->id = NW;
                    }
                    else if (myString[row][column][0] == 'B' and bishopValid(row, column, i, j, myString, myString[row][column]))
                    {
                        draw2(i, j);
                        this->curr_user->id = BW;
                    }
                    else if (myString[row][column][0] == 'Q' and queenValid(row, column, i, j, myString, myString[row][column]))
                    {
                        draw2(i, j);
                        this->curr_user->id = QW;
                    }
                    else if (myString[row][column][0] == 'R' and rookValid(row, column, i, j, myString, myString[row][column]))
                    {
                        draw2(i, j);
                        this->curr_user->id = RW;
                    }
                }
            }
        }
    }
    else if (turnForWhat == PLACESELECT)
    {
        if (this->curr_user->id == PW and pawnValid(this->curr_user->x, this->curr_user->y, row, column, myString, myString[curr_user->x][curr_user->y]))
        {
            cout << row  << " " << column << endl;
            myString[row][column] = myString[curr_user->x][curr_user->y];
            myString[curr_user->x][curr_user->y] = "--";
            this->cells[curr_user->x][curr_user->y].cell_status = EMPTY;
            turnForWhat = MOHRESELECT;
            run(myString);
        }
    }
    if (row == -1 || column == -1)
        return;
}

void Board::occupeted_cell_clicked(int row, int column)
{
    if (this->curr_user->id == PW) this->curr_user = this->pw;
    if (this->curr_user->id == PB) this->curr_user = this->pb;
    if (this->curr_user->id == BW) this->curr_user = this->bw;
    if (this->curr_user->id == BB) this->curr_user = this->bb;
    if (this->curr_user->id == NW) this->curr_user = this->nw;
    if (this->curr_user->id == NB) this->curr_user = this->nb;
    if (this->curr_user->id == QW) this->curr_user = this->qw;
    if (this->curr_user->id == QB) this->curr_user = this->qb;
    if (this->curr_user->id == KW) this->curr_user = this->kw;
    if (this->curr_user->id == KB) this->curr_user = this->kb;
    if (this->curr_user->id == RW) this->curr_user = this->rw;
    if (this->curr_user->id == RB) this->curr_user = this->rb;
}

void Board::cell_empty_clicked(int row, int column)
{
    put_xo_in_cell(row, column);
    this->end = this->curr_user->check_win(this->cells);
    if (this->end)
        return;
    // this->curr_user = this->curr_user->id == X ? this->user_o : this->user_x;
}

void Board::put_xo_in_cell(int row, int column)
{
    // cout << curr_user << endl;
    // this->curr_user->id = PW;
    XO* xo = new XO(this->curr_user->id);
    // cout << 1 << endl;
    xo->sprite.setPosition(this->cells[row][column].rect.getPosition());
    // cout << 2 << endl;
    this->cells[row][column].xo = xo;
    // cout << 3 << endl;
    this->cells[row][column].cell_status = OCCUPIED;
    // cout << 4 << endl;
}

void Board::update_status_text()
{
    if (this->end)
        status_text.setString(get_name_of_id(this->curr_user->id) + " Wins!");
    else
        status_text.setString(get_name_of_id(this->curr_user->id) + " Turn");
}