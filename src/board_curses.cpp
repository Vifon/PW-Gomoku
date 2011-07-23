#include "board_curses.hpp"

Board_curses::Board_curses(int x, int y) : no_del(false)
{
    win = newwin(N, N, y, x);
}

Board_curses::Board_curses(WINDOW* _win) : no_del(true),
                                           win(_win) { }

Board_curses::~Board_curses()
{
    if (!no_del) delwin(win);
}

void Board_curses::print()
{
    int x,y;
    getyx(win, y, x);
    for (int i=0; i<N; ++i)
    {
        for (int j=0; j<N; ++j)
        {
            wattron (win, COLOR_PAIR(arr[i][j]));
            if (arr[i][j] == NIC)
                mvwaddch(win, j, i, 'o');
            else
                mvwaddch(win, j, i, 'X');
            wattroff(win, COLOR_PAIR(arr[i][j]));
        }
    }
    ::wmove(win, y, x);
    wrefresh(win);
}
