#ifndef _BOARD_H_
#define _BOARD_H_ 1

#include <exception>

#ifndef N
    #define N 15
#endif

#ifndef GOAL
    #define GOAL 5
#endif

class square_occupied : std::exception { };

enum square { NIC, GUMA, BATON }; // sorry for the in-joke ;)

class Board
{
  private:
    bool check(int x, int y);
    bool checkLine(int x, int y, int hmove, int vmove, int range);
    
  protected:
    square arr[N][N];

  public:
    Board();
    virtual ~Board();
    bool move(square turn, int x, int y);
    virtual void print() = 0;
};

#endif
