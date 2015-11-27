/* 
 * File:   ChessBoard.cpp
 * Author: Julien
 * 
 * Created on 20 novembre 2015, 10:08
 */

#include "../Header/ChessBoard.hpp"

ChessBoard::ChessBoard() 
{
    ChessBoard(8);
}

ChessBoard::ChessBoard(int n) 
{
    N = n;
    Node::NodeExternalIDInit(nbTiles);
    tiles = new Node**[n];
    for(int i = 0; i < n; i++)
    {
        tiles[i] = new Node*[n];
        for(int j = 0; j < n ; j++)
           tiles[i][j] = new Node(nbTiles);
    }
    
    ConnectTiles();
}

ChessBoard::~ChessBoard() 
{
    for(int i = 0; i < N; i++)
    {    
        for(int j = 0; j< N ; j++)
        {
            delete tiles [i][j];
        }
        delete tiles[i];
    }
    delete tiles;
}

void ChessBoard::ConnectTiles(void)
{
    int connectionGrid[N][N][N][N];
    int rayon;
    
    for(int x1 = 0 ; x1 < N; x1++)
        for(int y1 = 0 ; y1 < N; y1++)
            for(int x2 = 0; x2 < N; x2++)
                for(int y2 = 0; y2 < N; y2++)
                {
                    connectionGrid[x1][y1][x2][y2] = -1;
                }
    
    for(int x1 = 0; x1 < N; x1++)
        for(int y1 = 0; y1 < N; y1++)
        {
            rayon = 1;
            connectionGrid[x1][y1][x1][y1] = 1;
            while(((x1+rayon)<N)||((x1-rayon)>=0)||((y1+rayon)<N)||((y1-rayon)>=0))
            {
                if(((x1-rayon)>=0)&&((y1-rayon)>=0))
                    connectionGrid[x1][y1][x1-rayon][y1-rayon] = 1;
                    
                if((x1-rayon)>=0)
                    connectionGrid[x1][y1][x1-rayon][y1] = 1;
                
                if(((x1-rayon)>=0)&&((y1+rayon)<N))
                    connectionGrid[x1][y1][x1-rayon][y1+rayon] = 1;
                
                if(((x1+rayon)<N)&&((y1-rayon)>=0))
                    connectionGrid[x1][y1][x1+rayon][y1-rayon] = 1;
                    
                if((x1+rayon)<N)
                    connectionGrid[x1][y1][x1+rayon][y1] = 1;
                
                if(((x1+rayon)<N)&&((y1+rayon)<N))
                    connectionGrid[x1][y1][x1+rayon][y1+rayon] = 1;
                
                if((y1+rayon)<N)
                    connectionGrid[x1][y1][x1][y1+rayon] = 1;
                
                if((y1-rayon)>=0)
                    connectionGrid[x1][y1][x1][y1-rayon] = 1;
                    
                rayon++;
            }
        }
    
    for(int x1 = 0 ; x1 < N; x1++)
        for(int y1 = 0 ; y1 < N; y1++)
            for(int x2 = 0; x2 < N; x2++)
                for(int y2 = 0; y2 < N; y2++)
                    if(x1!=x2 || y1!=y2)
                        Node::Connect(*tiles[x1][y1], *tiles[x2][y2], connectionGrid[x1][y1][x2][y2], connectionGrid[x2][y2][x1][y1]);
}

void ChessBoard::DrawConnection(int x, int y)
{
    tiles[x][y]->PrintConnection();
    
    for(int i = 0; i < N; i++)
    {
        cout << " ";
        for(int j = 0; j < N; j++)
        {
            if(i==x && j == y)
                cout << "x";
            else if(tiles[x][y]->SearchID(i*N+j)>-1)
                cout << "o";
            else
                cout << ".";
        }
        cout << endl;
    }
}

