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

/**
 * Permet de créer un échiquier de taille n x n
 * @param n taille de l'échiquier
 */
ChessBoard::ChessBoard(int n) 
{
    N = n;
    cout << "Initialisation d'un echequier de taille " << N << "x" << N << ":" << endl;
    Node::NodeExternalIDInit(nbTiles);
    cout << "Initialisation des tuiles de l'echequier :" << endl;
    tiles = new Node**[N];
    for(int i = 0; i < N; i++)
    {
        tiles[i] = new Node*[N];
        for(int j = 0; j < N ; j++)
        {
            cout << "(" << ((100*(i*N+j+1))/(N*N)) << "," << ((1000*(i*N+j+1))/(N*N))%10 <<"%)" << "\r";
            tiles[i][j] = new Node(nbTiles);
        }
    }
    cout << "Initialisation des tuiles de l'echequier : FIN" << endl;
    
    ConnectTiles();
    
    cout << "Initialisation d'un echequier de taille " << n << "x" << n << ": FIN" << endl << endl;
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

/**
 * Permet de calculer les connections entre les noeuds
 */
void ChessBoard::ConnectTiles(void)
{
    //int connectionGrid[N][N][N][N];
    int **** connectionGrid = new int***[N];
    int rayon;
    
    cout << "Initialisation de la liste des connexions : " << endl; 
    
    for(int i = 0; i<N;i++)
    {
        connectionGrid[i] = new int**[N];
        for(int j = 0; j<N;j++)
        {
            cout << "(" << ((100*(i*N+j+1))/(N*N)) << "," << ((1000*(i*N+j+1))/(N*N))%10 <<"%)" << "\r";
            connectionGrid[i][j] = new int*[N];
            for(int k = 0; k<N;k++)
            {
                connectionGrid[i][j][k] = new int[N];
                for(int l = 0; l<N;l++)
                {
                    connectionGrid[i][j][k][l] = -1;
                }
            }
        }
    }
    
    cout << "Initialisation de la liste des connexions : FIN" << endl;
    
    cout << "Calcul de la liste des connexions : " << endl;
    
    for(int x1 = 0; x1 < N; x1++)
        for(int y1 = 0; y1 < N; y1++)
        {
            cout << "(" << ((100*(x1*N+y1+1))/(N*N)) << "," << ((1000*(x1*N+y1+1))/(N*N))%10 <<"%)" << "\r";
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
    
    cout << "Calcul de la liste des connexions :  FIN " << endl;
    cout << "Application de la liste des connexions : " << endl;
    
    for(int x1 = 0 ; x1 < N; x1++)
        for(int y1 = 0 ; y1 < N; y1++)
        {    
            cout << "(" << ((100*(x1*N+y1+1))/(N*N)) << "," << ((1000*(x1*N+y1+1))/(N*N))%10 <<"%)" << "\r";
            for(int x2 = 0; x2 < N; x2++)
                for(int y2 = 0; y2 < N; y2++)
                    if(x1!=x2 || y1!=y2)
                        Node::Connect(*tiles[x1][y1], *tiles[x2][y2], connectionGrid[x1][y1][x2][y2], connectionGrid[x2][y2][x1][y1]);
        }
    cout << "Application de la liste des connexions : FIN" << endl;
    cout << "Nettoyage de la liste des connexions : " << endl;
                
    for(int i = 0; i<N;i++)
    {
        for(int j = 0; j<N;j++)
        {
            cout << "(" << ((100*(i*N+j+1))/(N*N)) << "," << ((1000*(i*N+j+1))/(N*N))%10 <<"%)" << "\r";
            for(int k = 0; k<N;k++)
            {
                delete connectionGrid[i][j][k];
            }
            delete connectionGrid[i][j];    
        }
        delete connectionGrid[i];
    }
    delete connectionGrid;
    cout << "Nettoyage de la liste des connexions : FIN " << endl;
}

/**
 * Affiche les tuiles connectées en une case (x,y)
 * @param x
 * @param y
 */
void ChessBoard::DrawTileConnection(int x, int y)
{
    //tiles[x][y]->PrintConnection();
    
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

/**
 * Affiche l'echiquier avec le fitness de chaque case
 */
void ChessBoard::DrawTileFitness(void)
{
    for(int i = 0; i < N; i++)
    {
        cout << " ";
        for(int j = 0; j < N; j++)
        {
            cout << tiles[i][j]->GetNbConflict() << "\t";
        }
        cout << endl;
    }    
}

/**
 * Calcul le fitness d'un chromosome (une liste de reine) avec temps de calcul
 * @param queenList Liste de reine d'un chromosome
 * @param tmpCalcul Temps de calcul
 * @return  La valeur de la fitness soit le nombre de conflit total
 */
int ChessBoard::CalculateFitness(int* queenList, unsigned long long &tmpCalcul)
{
    int currentNeighbor;
    int fitness = 0;
    
    ResetChessBoard();
    
    for(int index = 0; index < N; index++)
    {
        for(int indexNeighbor = 0; indexNeighbor < tiles[index][queenList[index]]->GetNbNeighbors(); indexNeighbor++)
        {
            tmpCalcul++;
            currentNeighbor = tiles[index][queenList[index]]->GetNeighbor(indexNeighbor);
            tiles[currentNeighbor/N][currentNeighbor%N]->SetNbConflict(tiles[currentNeighbor/N][currentNeighbor%N]->GetNbConflict()+1);
        }
    }
    
    for(int index = 0; index < N; index++)
    {
        fitness += tiles[index][queenList[index]]->GetNbConflict();
    }
    
    return fitness;
    
}

/**
 * Calcul le fitness d'un chromosome (une liste de reine)
 * @param queenList Liste de reine d'un chromosome
 * @return  La valeur de la fitness soit le nombre de conflit total
 */
int ChessBoard::CalculateFitness(int* queenList)
{
    int currentNeighbor;
    int fitness = 0;
    
    ResetChessBoard();
    
    for(int index = 0; index < N; index++)
    {
        for(int indexNeighbor = 0; indexNeighbor < tiles[index][queenList[index]]->GetNbNeighbors(); indexNeighbor++)
        {
            currentNeighbor = tiles[index][queenList[index]]->GetNeighbor(indexNeighbor);
            tiles[currentNeighbor/N][currentNeighbor%N]->SetNbConflict(tiles[currentNeighbor/N][currentNeighbor%N]->GetNbConflict()+1);
        }
    }
    
    for(int index = 0; index < N; index++)
    {
        fitness += tiles[index][queenList[index]]->GetNbConflict();
    }
    
    return fitness;
}

/**
 * Efface les données utilisée lors des calculs
 */
void ChessBoard::ResetChessBoard(void)
{
    for(int i = 0 ; i < N; i++)
    {
        for(int j = 0 ; j < N; j++)
        {
            tiles[i][j]->SetNbConflict(0);
            //tiles[i][j]->SetIsQueen(false);
        }
    }
}

/**
 * Dessine l'echiquier d'un chromosome 
 * @param queenList Un chromosome (liste de reines)
 */
void ChessBoard::DrawQueens(int * queenList)
{
    int queenPos;
    
    for(int i = 0; i < N; i++)
    {
        cout << " ";
        queenPos = queenList[i];
        for(int j = 0; j < N; j++)
        {
            if(j==queenPos)
            {
                cout << "Q";
            }
            else
            {
                cout << ".";
            }
        }
        cout << endl;
    }    
}
