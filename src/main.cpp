#include "board_curses.hpp"

void curPlayer(square turn)
{
    mvaddstr(0, 0, "Current player: ");
    if (turn == GUMA)
        addstr("Red ");
    else
        addstr("Blue");
}

int main(int argc, char *argv[])
{
    initscr();
    cbreak();
    noecho();
    start_color();
    mousemask(BUTTON1_CLICKED, NULL);
    mouseinterval(0);

    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);

    int          x,y;
    int          ch      = 0;
    square       turn    = GUMA;
    bool         winner  = false;
    WINDOW*      win_big = newwin(N+2, N+2, 1, 0);
    WINDOW*      win     = derwin(win_big, N, N, 1, 1);
    Board_curses b(win);
    MEVENT       event;
    keypad(win, 1);
    box(win_big, 0, 0);
    curPlayer(turn);
    refresh();
    wrefresh(win_big);
    b.print();
    wmove(win, 0, 0);
    while(!winner)
    {
        bool restart_loop = false;
        bool mouse        = false;
        while (!mouse && (ch = wgetch(win)) != '\n')
        {
            getyx(win, y, x);
            switch (ch)
            {
                case KEY_UP:
                    if (y > 0)
                        wmove(win, --y, x);
                    break;
                case KEY_DOWN:
                    if (y < N-1)
                        wmove(win, ++y, x);
                    break;
                case KEY_LEFT:
                    if (x > 0)
                        wmove(win, y, --x);
                    break;
                case KEY_RIGHT:
                    if (x < N-1)
                        wmove(win, y, ++x);
                    break;
                case KEY_MOUSE:
                    if (getmouse(&event) == OK && ( event.bstate & BUTTON1_CLICKED ) )
                    {
                        event.x -= 1;
                        event.y -= 2;
                        if( event.x <  N &&
                            event.x >= 0 &&
                            event.y <  N &&
                            event.y >= 0 )
                        {
                            wmove(win, event.y, event.x);
                            mouse = true;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        getyx(win, y, x);
        
        try
        {
            winner = b.move(turn, x, y);
        }
        catch (square_occupied)
        {
            restart_loop = true;
        }
        if (!restart_loop)
        {
            if (!winner)
            {
                if (turn == GUMA)
                    turn = BATON;
                else
                    turn = GUMA;
            }
            b.print();
            curPlayer(turn);
            refresh();
            wmove(win, y, x);
        }
    }

    endwin();
    
    if (turn == GUMA)
        puts("Red player is a winrar");
    else
        puts("Blue player is a winrar");
    return 0;
}
