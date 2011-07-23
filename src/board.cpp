#include "board.hpp"

Board::Board()
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            arr[i][j]=NIC;
        }
    }
}

Board::~Board() { }

bool Board::move(square turn, int x, int y)
{
    if(arr[x][y] != NIC)
        throw square_occupied();

    arr[x][y]=turn;
    return check(x,y);
}

bool Board::check(int x, int y)
{
    return ( checkLine(x, y,  1, 0, 5) ||
             checkLine(x, y,  0, 1, 5) ||
             checkLine(x, y,  1, 1, 5) ||
             checkLine(x, y, -1, 1, 5) );
}

bool Board::checkLine(int x, int y, int hstep, int vstep, int range)
{
    int c=0;
    for ( int i=x-(range*hstep), j=y-(range*vstep);
          i <= x+(range*hstep) && j <= y+(range*vstep);
          i=i+hstep, j=j+vstep )
    {
        if(c < range)
            if(arr[i][j] == arr[x][y])
                ++c;
            else
                c=0;
        else
            if(arr[i][j] == arr[x][y])
                c=0;
            else
                return 1;
    }
    return 0;
}
