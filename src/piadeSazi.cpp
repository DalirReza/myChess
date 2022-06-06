#include<iostream>
#include<vector>
using namespace std;
class theBoard
{
public :
    string myBoard2[8][8];
    void setDefault()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                myBoard2[i][j] = "--";
        }
    }
    void setMohre(int x, int y, string piece)
    {
        myBoard2[x][y] = piece;
    }
    void deleteMohre(int x, int y)
    {
        myBoard2[x][y] = "--";
    }
    void Move(int exx, int exy, int x, int y, string piece)
    {
        myBoard2[x][y] = piece;
        myBoard2[exx][exy] = "--";
    }
};

class Mohre
{
public:
    int x, y;
    string MohreName, theIcon;
    Mohre(){}
    Mohre(int x, int y)
    {
        this -> x = x;
        this -> y = y;
    }
    void getDelete(int x, int y, theBoard mb)
    {
        mb.deleteMohre(x, y);
    }
    void setTheMohre(string name, theBoard& mb)
    {
        mb.setMohre(x, y, name);
        this -> MohreName = name;
    }
    void moveTheMohre(int x ,int y, bool validation, theBoard& tb)
    {
        if (validation)
        {

            // tb.myBoard[x][y] = MohreName;
            // tb.deleteMohre(this -> x, this -> y);
            // // tb.myBoard[thi]
            // // tb[x][y] = MohreName;
            // tb.myBoard[this -> x][this -> y] = "--";
            tb.Move(this -> x, this -> y, x, y, MohreName);
            this -> x = x;
            this -> y = y;
        }
    }
};

class Pawn : public Mohre
{
public :
    Pawn(){}
    Pawn(int x, int y)
    {
        this -> x = x;
        this -> y = y;
    }
    bool pawnValid(int desI, int desJ, string tb[8][8])
    {
        if((desI!=this->x or desJ!=this->y) and (tb[desI][desJ]=="--") and (desI<8 and desJ<8 and desI>=0 and desJ>=0))
        {
            if(this -> MohreName[1] == 'B')
            {
                if (this -> x == 1 and (desI == 2 or desI == 3) and desJ == this->y)
                {
                    return true;
                }
                else if (this -> x != 1 and desI == this -> x + 1 and desJ == this->y)
                    return true;
            }
            else 
            {
                if (this -> x = 6 and (desI == 5 or desI == 4) and desJ == this->y)
                    return true;
                else if (this -> x != 6 and desI == this -> x - 1 and desJ == this->y)
                    return true;
            }
        }
        else if((desI != this -> x or desJ != this -> y) and (tb[desI][desJ][1] == 'B') and MohreName[1] == 'W' and
        (desI == this -> x-1 ) and (desJ == this -> y+1 or desJ == this -> y-1))
            return true;
        else if((desI != this -> x or desJ != this -> y) and (tb[desI][desJ][1] == 'W') and MohreName[1] == 'B' and
        (desI == this-> x+1) and (desJ == this->y+1 or desJ == this -> y-1))
            return true;
        return false;
    }
};

class Bishop : public Mohre
{
public :
    Bishop(){}
    Bishop(int x, int y)
    {
        this -> x = x;
        this -> y = y;
    }
    bool bishopValid(int desI, int desJ, string tb[8][8])
    {
        if (desI>=0 and desJ>=0 and desI<8 and desJ<8) 
        {
            if((tb[desI][desJ] == "--" and (x+desJ == y+desI or x+desI == y+desJ)) or (tb[desI][desJ][1] != MohreName[1] and (x+desJ == y+desI or x+desI == y+desJ)))
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
};

class Knight : public Mohre
{
public :
    Knight(){}
    Knight(int x, int y)
    {
        this -> x = x;
        this -> y = y;
    }
    bool knightValid(int desI, int desJ, string tb[8][8])
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
};

class Rook : public Mohre
{
public :
    Rook(){}
    Rook(int x, int y)
    {
        this -> x = x;
        this -> y = y; 
    }
    bool rookValid(int desI, int desJ, string tb[8][8])
    {
        if (desI>=0 and desI<8 and desJ>=0 and desJ<8)
        {
            if ((tb[desI][desJ] == "--" or tb[desI][desJ][1] != MohreName[1]) and (desI == x or desJ == y))
            {
                if (desI == x)
                {
                    int myMaxJ = max(desJ, y), myMinJ = (desJ, y);
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
};

class Queen : public Mohre
{
public :
    Queen(){}
    Queen(int x, int y)
    {
        this -> x = x;
        this -> y = y;
    }
    bool queenValid(int desI, int desJ, string tb[8][8])
    {
        if (desI>=0 and desJ>=0 and desI<8 and desJ<8) 
        {
            if((tb[desI][desJ] == "--" and (x+desJ == y+desI or x+desI == y+desJ)) or (tb[desI][desJ][1] != MohreName[1] and (x+desJ == y+desI or x+desI == y+desJ)))
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
                    int myMaxJ = max(desJ, y), myMinJ = (desJ, y);
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
};


class King : public Mohre
{
public :
    // friend Pawn;
    King(){}
    Pawn* myPans;
    Knight* myKinghts;
    Bishop* myBishops;
    Rook* myRook;
    Queen myQueen ;
    King(int x, int y, Pawn* myPans, Knight* myKinghts, Bishop* myBishops, Rook* myRook, Queen myQueen , King myKing)
    {
        this -> x = x;
        this -> y = y;
        this-> myPans = myPans;
        this-> myKinghts = myKinghts;
        this-> myBishops = myBishops;
        this-> myRook = myRook;
        this-> myQueen = myQueen;
    }
    bool therad(int desI, int desJ, string tb[8][8], char color)
    {
        for (int i = 0; i < 16; i++)
        {
            if (myPans[i].MohreName[1] == color)
            {
                if (color == 'W') tb[desI][desJ] == "PB";
                else tb[desI][desJ] == "PW";
                if (myPans[i].pawnValid(desI, desJ, tb))
                {
                    tb[desI][desJ] = MohreName;
                    return true;
                }
            }
        }
        tb[desI][desJ] = "--";
        for (int i = 0; i < 4; i++)
        {
            if (myBishops[i].MohreName[1] == color and myBishops[i].bishopValid(desI, desJ, tb))
                return true;
        }
        for (int i = 0; i < 4; i++)
        {
            if (myKinghts[i].MohreName[1] == color and myKinghts[i].knightValid(desI, desJ, tb))
                return true;
        }
        for (int i = 0; i < 4; i++)
        {
            if (myRook[i].MohreName[1] == color and myRook[i].rookValid(desI, desJ, tb))
                return true;
        }
        if (myQueen.MohreName[1] == color and myQueen.queenValid(desI, desJ, tb))
            return true;
        tb[desI][desJ] = MohreName;
        return false;
    }
    bool KingValid(int desI, int desJ, string tb[8][8])
    {
        if ((desI>=0 and desJ>=0 and desI<8 and desJ<8)) 
        {
            if ((desI == x-1 and (desJ == y-1 or desJ == y+1 or desJ == y) and tb[desI][desJ] == "--")
            or (tb[desI][desJ][1] == MohreName[1] and therad(desI, desJ, tb, MohreName[1]))
            or (desI == x and (desJ == y-1 or desJ == y+1) and tb[desI][desJ] == "--")
            or (tb[desI][desJ][1] == MohreName[1] and therad(desI, desJ, tb, MohreName[1]))
            or (desI == x+1 and (desJ == y-1 or desJ == y+1 or desJ == y) and tb[desI][desJ] == "--")
            or (tb[desI][desJ][1] == MohreName[1] and therad(desI, desJ, tb, MohreName[1])))
                return true;
        }
        return false;
    }
    bool check(string tb[8][8])
    {
        if (therad(x, y, tb, MohreName[1]))
            return true;
        return false;
    }

    bool mate(string tb[8][8])
    {
        if (check(tb))
        {
            for (int i = x-1; i <= x+1; i++)
            {
                for (int j = y-1; j <= y+1; j++)
                {
                    if (i < 0 or j < 0) continue;
                    if (tb[i][j][1] == MohreName[1]) continue;
                    if (i == x and j == y) continue;
                    if (therad(i, j, tb, MohreName[1])) continue;
                    else return false;
                }
            }
        }
        if (MohreName[1] == 'W') cout << "black wins!";
        else cout << "white wins!";
        exit(0);
    }
};

// char changeTurn(char turn)
// {
//     if (turn == 'W')
//         return 'B';
//     else return 'W';
// }



// bool backTrack(theBoard myBoard, Pawn *myPawns, Bishop *myBishop, Rook *myRook, Knight *myKnight, King myKing, Queen myQueen, char turn, int first, int second)
// {
//     if (first == 4 and myKing.mate(myBoard.myBoard2)) return true; 
//     for (int i = 0; i < 16; i++)
//     {
//         if (myPawns[i].MohreName[1] == turn)
//         {

//         }
//     }
// }


// void theMain()
// {
//     string temp;
//     static char turn;
//     turn = 'W';
//     theBoard myBoard;
//     Pawn myPawns[16];
//     Bishop myBishops[4];
//     Knight myKnights[4];
//     Rook myRook[4];
//     King kingSefid, kingSiah;
//     Queen queenSefid, queenSiah;
//     int var=0, var1=0, var2=0, var3=0;
//     for (int i = 0; i < 64; i++)
//     {
//         string kind, color;
//         cin >> temp;
//         if (temp != "--")
//         {
//             kind = temp[0];
//             color = temp[1];
//             if (kind == "P")
//             {
//                 Pawn x(i/8, i%8);
//                 x.setTheMohre(temp, myBoard);
//                 myPawns[var1] = x;
//                 var1++;
//             }
//             if (kind == "N")
//             {
//                 Knight x(i/8, i%8);
//                 x.setTheMohre(temp, myBoard);
//                 myKnights[var2] = x;
//                 var2++;
//             }
//             if (kind == "K")
//             {

//                 if (color == "W")
//                 {
//                     King x(i/8, i%8, myPawns, myKnights, myBishops, myRook, queenSefid, kingSefid);
//                     x.setTheMohre(temp, myBoard);
//                     kingSefid = x;
//                 }
//                 else
//                 {
//                     King x(i/8, i%8, myPawns, myKnights, myBishops, myRook, queenSiah, kingSiah);
//                     x.setTheMohre(temp, myBoard);
//                     kingSiah = x;
//                 }
//             }
//             if (kind == "Q")
//             {
//                 Queen x(i/8, i%8);
//                 x.setTheMohre(temp, myBoard);
//                 if (color == "W")
//                     queenSefid = x;
//                 else queenSiah = x;
//             }
//             if (kind == "B")
//             {
//                 Bishop x(i/8, i%8);
//                 x.setTheMohre(temp, myBoard);
//                 myBishops[var3] = x;
//                 var3++;
//             }
//             if (kind == "R")
//             {
//                 Rook x(i/8, i%8);
//                 x.setTheMohre(temp, myBoard);
//                 myRook[var] = x;
//                 var++;
//             }
//         }
//     }

//     // backTrack(myBoard, myPawns, myBishops, myRook, myKnights, kingSefid, queenSefid);
//     // for (int i = 0; i < 8; i++)
//     // {
//     //     for (int j = 0; j < 8; j++)
//     //     {
//     //         if (myBoard.myBoard[i][j] == "--") continue;
//     //         for (int k = 0; k < 16; k++)
//     //         {
//     //             if (myPawns[k].pawnValid(i, j, myBoard.myBoard))
//     //             {
//     //             }
//     //             for (int t = 0; t < 8; t++)
//     //             {
//     //                 // if ()
//     //             }
//     //         }
//     //     }
//     // }
//     //     for (int i = 0; i < 32; i++)
//     //     {
//     //         if (myArray[i].MohreName == command.substr(2, 2))
//     //         {
//     //             if (myArray[i].y == (int)command[0]-97 and 8-myArray[i].x == (int)command[1]-48)
//     //             {
//     //                 myArray[i].moveTheMohre((int)command[4]-97, 8-8-((int)command[5]-48), true, myBoard);
//     //             }
//     //         }
//     //     }
//     // }   
// }