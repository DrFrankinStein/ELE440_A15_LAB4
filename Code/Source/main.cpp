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
    int N = 16;
    ChessBoard c(N);
    
    c.DrawConnection(4,4);
    
    return 0;
}

