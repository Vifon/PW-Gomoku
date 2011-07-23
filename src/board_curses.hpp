#ifndef _BOARD_CURSES_H_
#define _BOARD_CURSES_H_ 1

#include "board.hpp"
#include <ncurses.h>

class Board_curses : public Board
{
  private:
    const bool no_del;
    WINDOW*    win;

  public:
    Board_curses(int x, int y);
    Board_curses(WINDOW* win);
    ~Board_curses();
    void print();
};

#endif
