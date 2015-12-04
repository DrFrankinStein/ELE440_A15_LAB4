/* 
 * File:   main.cpp
 * Author: Julien
 *
 * Created on 20 novembre 2015, 09:56
 */

#include <cstdlib>
#include "../Header/ChessBoard.hpp"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
    int N = 4;
    ChessBoard c(N);
    
    //c.DrawTileConnection(4,4);
    int Z;
    
    int list[4] = {0,1,3,2};
    
    Z = c.PlaceQueens(list);
    cout << Z;
    return 0;
}

