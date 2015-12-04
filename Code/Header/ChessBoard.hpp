/* 
 * File:   ChessBoard.hpp
 * Author: Julien
 *
 * Created on 20 novembre 2015, 10:08
 */

#ifndef CHESSBOARD_HPP
#define	CHESSBOARD_HPP

#include "../Header/Node.hpp"

class ChessBoard 
{
public:
    ChessBoard();
    ChessBoard(int n);
    virtual ~ChessBoard();
    
    void DrawTileConnection(int x, int y);
    int PlaceQueens(int* queenList);
    int CalculateFitness(int* queenList);
    void ResetChessBoard(void);
    void DrawTileFitness(void);
    
private:
    
    void ConnectTiles(void);
    int N;
    int nbTiles;
    Node ***tiles;

};

#endif	/* CHESSBOARD_HPP */

