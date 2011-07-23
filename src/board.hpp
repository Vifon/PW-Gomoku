#ifndef _BOARD_H_
#define _BOARD_H_ 1

#include <exception>
#include <ncurses.h>

#define N 15

class square_occupied : std::exception { };

enum square { NIC = 'o', GUMA = 'X', BATON = 'Y' }; // sorry for the in-joke ;)

class Board
{
  public:
    Board();
    bool move(square,int,int);
    void print(square);
  protected:
    square arr[N][N];
    bool check(int,int);
};

#endif
