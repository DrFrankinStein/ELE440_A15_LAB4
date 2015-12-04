/*
 * Nom : generalFunctions.cpp
 * Auteur : Julien Lemay & Alexandre Lessard
 * Description : Contient plusieurs fonctions nécessaire au deroulement du
 *               programme.
 * Date : 20/11/15
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <climits>
#include <ctime>

using namespace std;

void GenererChromosomes(int **tableau, int P, int N)
{
    // Définition des variables
    
    // Debut du programme
    srand(time(NULL));
    for(int i = 0; i < P; i++)
    {
        for(int j = 0; j < N; j++)
        {
            tableau[i][j] = rand()%N;
        }
    }
}

void xChange (int index1, int index2, int *matrix)
{
    // Définition des variables
    int temp; // Variable temporaire
    
    // Debut du program
    
    temp = matrix[index1];
    matrix[index1] = matrix[index2];
    matrix[index2] = temp;
}

void shiftLeft(int N, int *matrix)
{
    // Déclaration des variables
    int temp; // variable temporaire.
    
    // Début du programme
    
    temp = matrix[0];
    for (int i = 0; i < N-1; i++)
    {
        matrix[i] = matrix[i+1];
    }
    matrix[N-1] = temp;
}

void shiftRight(int N, int *matrix)
{
    // Déclaration des variables
    int temp; // variable temporaire.
    
    // Début du programme
    
    temp = matrix[N-1];
    for (int i = N-1; i >= 0; i--)
    {
        matrix[i] = matrix[i-1];
    }
    matrix[0] = temp;
}