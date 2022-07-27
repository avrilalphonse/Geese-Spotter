#include "geesespotter_lib.h"
#include <iostream>

//functions
char* createBoard(std::size_t xdim, std::size_t ydim) //1
{
    std::size_t cap = xdim*ydim;
    char* board{ new char[cap] {}};
    return board;
}//end *createBoard

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim)
{
    for(int point{0}; point < xdim*ydim; ++point)
    {
        if(board[point] == 9)
        {
            if(point%xdim == 0 && point/xdim == 0)
            {
                for(int i{0}; i < 2; ++i) // y
                {
                    for(int j{0}; j < 2; ++j) // x
                    {
                        if(board[point + (xdim*i) + j] != 9)
                        {
                            board[point + (xdim*i) + j] += 1;
                        }
                    }//nested loop
                }//outer for loop
            } else if(point%xdim == xdim-1 && point/xdim == 0)
            {
                for(int i{0}; i < 2; ++i) // y
                {
                    for(int j{-1}; j < 1; ++j) // x
                    {
                        if(board[point + (xdim*i) + j] != 9)
                        {
                            board[point + (xdim*i) + j] += 1;
                        }
                    }//nested loop
                }//outer for loop
            } else if(point%xdim == 0 && point/xdim == ydim-1)
            {
                for(int i{-1}; i < 1; ++i) // y
                {
                   for(int j{0}; j < 2; ++j) // x
                    {
                        if(board[point + (xdim*i) + j] != 9)
                        {
                            board[point + (xdim*i) + j] += 1;
                        }
                    }//nested loop
                }//outer for loop
            } else if(point%xdim == xdim-1 && point/xdim == ydim-1)
            {
                for(int i{-1}; i < 1; ++i) // y
                {
                   for(int j{-1}; j < 1; ++j) // x
                    {
                        if(board[point + (xdim*i) + j] != 9)
                        {
                            board[point + (xdim*i) + j] += 1;
                        }
                    }//nested loop
                }//outer for loop
            } else if(point%xdim == 0)
            {
                for(int i{-1}; i < 2; ++i) // y
                {
                    for(int j{0}; j < 2; ++j) // x
                    {
                        if(board[point + (xdim*i) + j] != 9)
                        {
                            board[point + (xdim*i) + j] += 1;
                        }
                    }//nested loop
                }//outer for loop
            } else if(point%xdim == xdim-1)
            {
                for(int i{-1}; i < 2; ++i) // y
                {
                    for(int j{-1}; j < 1; ++j) // x
                    {
                        if(board[point + (xdim*i) + j] != 9)
                        {
                            board[point + (xdim*i) + j] += 1;
                        }
                    }//nested loop
                }//outer for loop
            } else if(point/xdim == 0)
            {
                for(int i{0}; i < 2; ++i) // y
                {
                   for(int j{-1}; j < 2; ++j) // x
                    {
                        if(board[point + (xdim*i) + j] != 9)
                        {
                            board[point + (xdim*i) + j] += 1;
                        }
                    }//nested loop
                }//outer for loop
            } else if(point/xdim == ydim-1)
            {
                for(int i{-1}; i < 1; ++i) // y
                {
                   for(int j{-1}; j < 2; ++j) // x
                    {
                        if(board[point + (xdim*i) + j] != 9)
                        {
                            board[point + (xdim*i) + j] += 1;
                        }
                    }//nested loop
                }//outer for loop
            } else
            {
                for(int i{-1}; i < 2; ++i) // y
                {
                   for(int j{-1}; j < 2; ++j) // x
                    {
                        if(board[point + (xdim*i) + j] != 9)
                        {
                            board[point + (xdim*i) + j] += 1;
                        }
                    }//nested loop
                }//outer for loop
            }//inner if
        }// outer if
    }

}//end computeNeighbour

void hideBoard(char *board, std::size_t xdim, std::size_t ydim) //2
{
    for(std::size_t i{0}; i < (xdim*ydim); ++i)
    {
        board[i]= board[i] | hiddenBit();
    }
}//end hideBoard

void cleanBoard(char *board) //3
{
    delete[] board;
    board = nullptr;
}//end cleanBoard

void printBoard(char *board, std::size_t xdim, std::size_t ydim) //4
{
    for(std::size_t y{0}; y < ydim; y++) // col
    {
        for(std::size_t x{0}; x < xdim; x++) // row
        {
            if((board[y*xdim + x] & markedBit()) != 0)
            {
                std::cout << "M";
            } else if(board[y*xdim + x] & hiddenBit())
            {
                std::cout << "*";
            } else
            {
                std::cout << (board[y*xdim + x] & valueMask());//( & valueMask());
            }//endif
        }//end for x
        std::cout << std::endl;
    }//end for y
}//end printBoard

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
    int point{0};
    point = yloc*xdim + xloc;
    if(board[yloc*xdim + xloc] & markedBit())
    {
        return 1;
    } else if(board[(yloc*xdim + xloc)] == (board[(yloc*xdim + xloc)] & ~hiddenBit()))
    {
        return 2;
    } else if(board[point] == 0x29)
    {
        board[yloc*xdim + xloc] = board[yloc*xdim + xloc] & ~hiddenBit();
        return 9;
    } else
    {
        board[yloc*xdim + xloc] = board[yloc*xdim + xloc] & ~hiddenBit();
    }
    if(board[point] == 0)
    {
        if(point%xdim == 0 && point/xdim == 0)
        {
            for(int i{0}; i < 2; ++i) // y
            {
                for(int j{0}; j < 2; ++j) // x
                {
                    board[point + (xdim*i) + j] = board[point + (xdim*i) + j] & ~hiddenBit();
                }//nested loop
            }//outer for loop
        } else if(point%xdim == xdim-1 && point/xdim == 0)
        {
            for(int i{0}; i < 2; ++i) // y
            {
                for(int j{-1}; j < 1; ++j) // x
                {
                    board[point + (xdim*i) + j] = board[point + (xdim*i) + j] & ~hiddenBit();
                }//nested loop
            }//outer for loop
        } else if(point%xdim == 0 && point/xdim == ydim-1)
        {
            for(int i{-1}; i < 1; ++i) // y
            {
               for(int j{0}; j < 2; ++j) // x
                {
                    board[point + (xdim*i) + j] = board[point + (xdim*i) + j] & ~hiddenBit();
                }//nested loop
            }//outer for loop
        } else if(point%xdim == xdim-1 && point/xdim == ydim-1)
        {
            for(int i{-1}; i < 1; ++i) // y
            {
               for(int j{-1}; j < 1; ++j) // x
                {
                    board[point + (xdim*i) + j] = board[point + (xdim*i) + j] & ~hiddenBit();
                }//nested loop
            }//outer for loop
        } else if(point%xdim == 0)
        {
            for(int i{-1}; i < 2; ++i) // y
            {
                for(int j{0}; j < 2; ++j) // x
                {
                    board[point + (xdim*i) + j] = board[point + (xdim*i) + j] & ~hiddenBit();
                }//nested loop
            }//outer for loop
        } else if(point%xdim == xdim-1)
        {
            for(int i{-1}; i < 2; ++i) // y
            {
                for(int j{-1}; j < 1; ++j) // x
                {
                    board[point + (xdim*i) + j] = board[point + (xdim*i) + j] & ~hiddenBit();
                }//nested loop
            }//outer for loop
        } else if(point/xdim == 0)
        {
            for(int i{0}; i < 2; ++i) // y
            {
                for(int j{-1}; j < 2; ++j) // x
                {
                    board[point + (xdim*i) + j] = board[point + (xdim*i) + j] & ~hiddenBit();
                }//nested loop
            }//outer for loop
        } else if(point/xdim == ydim-1)
        {
            for(int i{-1}; i < 1; ++i) // y
            {
                for(int j{-1}; j < 2; ++j) // x
                {
                    board[point + (xdim*i) + j] = board[point + (xdim*i) + j] & ~hiddenBit();
                }//nested loop
            }//outer for loop
        } else
        {
            for(int i{-1}; i < 2; ++i) // y
            {
               for(int j{-1}; j < 2; ++j) // x
                {
                    board[point + (xdim*i) + j] = board[point + (xdim*i) + j] & ~hiddenBit();
                }//nested loop
            }//outer for loop
        }//inner if
    }//outer if
    return 0;
}//end reveal

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) //5
{
    if(board[(yloc*xdim + xloc)] == (board[(yloc*xdim + xloc)] & ~hiddenBit()))
    {
        return 2;
    }
    if(board[yloc*xdim + xloc] & markedBit())
    {
        board[yloc*xdim + xloc] = board[yloc*xdim + xloc] & ~markedBit();
    }else
    {
        board[yloc*xdim + xloc] = board[yloc*xdim + xloc] | markedBit();
    }
    return 0;
}//end mark

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim)
{
    for(int i{0}; i < xdim*ydim; ++i)
    {
        if(board[i] & hiddenBit() && (board[i] & valueMask()) != 9)
        {
            return false;
        }
    }
    return true;
}//end isGameWon
