#include "board.hpp"

int main(int argc, char *argv[])
{
    initscr();
    cbreak();
    keypad(stdscr, 1);
    noecho();
    start_color();
    mousemask(BUTTON1_CLICKED, NULL);
    mouseinterval(0);
    refresh();

    int x,y;
    square turn = GUMA;
    bool win = false;
    Board b;
    int ch = 0;
    MEVENT event;
    b.print(turn);
    move(1,0);
    while(!win)
    {
        bool mouse = false;
        while (!mouse && (ch = getch()) != '\n')
        {
            getyx(stdscr, y, x);
            switch (ch)
            {
                case KEY_UP:
                    if (y > 1)
                        move(--y, x);
                    break;
                case KEY_DOWN:
                    if (y < N)
                        move(++y, x);
                    break;
                case KEY_LEFT:
                    if (x > 0)
                        move(y, --x);
                    break;
                case KEY_RIGHT:
                    if (x < N-1)
                        move(y, ++x);
                    break;
                case KEY_MOUSE:
                    if (getmouse(&event) == OK && ( event.bstate & BUTTON1_CLICKED ) )
                    {
                        if(event.x < N &&
                           event.x >= 0 &&
                           event.y < N+1 &&
                           event.y > 0)
                        {
                            move(event.y, event.x);
                            mouse = true;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        getyx(stdscr, y,x);
        
        try
        {
            win = b.move(turn,x,--y);
        }
        catch (square_occupied)
        {
            continue;
        }
        if (!win)
            if (turn == GUMA) turn = BATON;
            else turn = GUMA;
        b.print(turn);
    }

    endwin();
    
    printf("%c is a winrar\n", turn);
    return 0;
}
