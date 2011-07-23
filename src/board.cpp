#include "board.hpp"

Board::Board()
{
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            arr[i][j]=NIC;
        }
    }
}

bool Board::move(square turn, int x, int y)
{
    if(arr[x][y] != NIC)
        throw square_occupied();

    arr[x][y]=turn;
    return check(x,y);
}

bool Board::check(int x, int y)
{
    int c=0;
    for(int i=x-5; i<=x+5; i++)
    {
        if(c<5)
            if(arr[i][y]==arr[x][y])
                c++;
            else
                c=0;
        else
            if(arr[i][y]==arr[x][y])
                c=0;
            else
                return 1;
    }
    c=0;
    for(int i=y-5; i<=y+5; i++)
    {
        if(c<5)
            if(arr[x][i]==arr[x][y])
                c++;
            else
                c=0;
        else
            if(arr[x][i]==arr[x][y])
                c=0;
            else
                return 1;
    }
    c=0;
    for(int i=x-5,j=y-5; i<=x+5 && j<=y+5; i++, j++)
    {
        if(c<5)
            if(arr[i][j]==arr[x][y])
                c++;
            else
                c=0;
        else
            if(arr[i][j]==arr[x][y])
                c=0;
            else
                return 1;
    }
    c=0;
    for(int i=x+5,j=y-5; i<=x-5 && j<=y+5; i--, j++)
    {
        if(c<5)
            if(arr[i][j]==arr[x][y])
                c++;
            else
                c=0;
        else
            if(arr[i][j]==arr[x][y])
                c=0;
            else
                return 1;
    }
    return 0;
}

void Board::print(square turn)
{
    int x,y;
    getyx(stdscr, y,x);
    mvaddch(0,0, (char)turn);
    for (int i=0;i<N;++i)
    {
        for (int j=0;j<N;++j)
        {
            if (arr[i][j] == GUMA)
                attron(COLOR_PAIR(1));
            else if (arr[i][j] == BATON)
                attron(COLOR_PAIR(2));
            mvaddch(j+1,i, (char) arr[i][j] );
            if (arr[i][j] == GUMA)
                attroff(COLOR_PAIR(1));
            else if (arr[i][j] == BATON)
                attroff(COLOR_PAIR(2));
        }
    }
    ::move(y,x);
}
