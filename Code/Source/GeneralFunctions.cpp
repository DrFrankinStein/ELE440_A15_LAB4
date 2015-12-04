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

#include "../Header/GeneralFunctions.hpp"

using namespace std;

void GenererChromosomes(int **tableau, int P, int N)
{
    // Définition des variables
    int tmp, rnd;
    // Debut du programme
    for(int i = 0; i < P; i++)
    {
        for(int j = 0; j < N; j++)
        {
            tableau[i][j] = j;
        }
        
        for(int j = N-1; j >= 0; j--)
        {
            rnd = rand()%(j+1);
            tmp = tableau[i][j];
            tableau[i][j] = tableau[i][rnd];
            tableau[i][rnd] = tmp;
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

void Recombinaison(int N, int P, int **parent, int **enfant)
{
    
    int listRecomb[N];
    int tmp, rnd, nbRecomb;
    int * PosToChange;
    
    
    for(int i = 0; i < N; i++)
        listRecomb[i] = i/2;
    
    int ListeParent[P];
    
    for(int j = 0; j < P; j++)//Mélangé index parent
    {
        ListeParent[j] = j;
    }

    for(int j = P-1; j >= 0; j--) //Génère couple parent au hasard
    {
        rnd = rand()%(j+1);
        tmp = ListeParent[j];
        ListeParent[j] = ListeParent[rnd];
        ListeParent[rnd] = tmp;
    }
    
    for(int j = 0; j < P; j++) // Créer enfants à partir de parents
    {
        for(int i = 0; i < N; i++)
        {
            enfant[j][i] = parent[ListeParent[j]][i];
        } 
    }
    
    
    for(int j = 0; j < P/2; j++) //Croisement
    {
        
        nbRecomb = listRecomb[rand()%10]; // nb de recombinaison par couple
        if(nbRecomb>0)
        {
            PosToChange = new int[nbRecomb*2]; //position a intervertir par paquet de 2
        
            for(int i =0; i<nbRecomb*2; i++) // Établissement des positions a intervertir
            {
                PosToChange[i] = rand()%N;
            }
            
            for(int i = 0; i<nbRecomb; i++)
            {
                for(int k = 0; k < 2; k++) // pour les 2 enfants
                {
                    tmp = enfant[j*2+k][PosToChange[i*2]];
                    enfant[j*2+k][PosToChange[i*2]] = enfant[j*2+k][PosToChange[i*2+1]];
                    enfant[j*2+k][PosToChange[i*2+1]] = tmp;
                }
            }

            delete PosToChange;
        }
    }
}

void Mutation(int N, int P, int **enfant)
{
    int indiceMutation = 25;
    int rnd, tmp;
    
    for(int i = 0; i < P ; i++)
    {
        rnd = rand()%100;
        if(rnd<=indiceMutation)
        {
            rnd = rand()%(2*N)+1;
            if(rnd<N)
            {
                tmp = enfant[i][rnd-1];
                enfant[i][rnd-1] = enfant[i][rnd];
                enfant[i][rnd] = tmp;
            }
        }
    }
}

void Combat(int N, int P, int **parent, int **enfant, ChessBoard *board)
{
    int **nouveau_parent = new int*[P];
    for(int i = 0; i < P; i++)
    {
        nouveau_parent[i] = new int[N];
    }
    
    int ListeCombat[2 * P];
    int rnd, tmp, win;
    int combatant[2];
    
    for(int j = 0; j < 2*P; j++)//Mélangé index parent
    {
        ListeCombat[j] = j;
    }

    for(int j = 2*P-1; j >= 0; j--) //Génère couple parent au hasard
    {
        rnd = rand()%(j+1);
        tmp = ListeCombat[j];
        ListeCombat[j] = ListeCombat[rnd];
        ListeCombat[rnd] = tmp;
    }
    
    
    for(int i =0; i<P; i++)
    {
        for(int c=0; c<2; c++)
        {
            if(ListeCombat[2*i+c]>=P)
                combatant[c]= board->CalculateFitness(enfant[ListeCombat[2*i+c]%P]);
            else
                combatant[c]= board->CalculateFitness(parent[ListeCombat[2*i+c]]);
        }
        
        if(combatant[0]<=combatant[1])
        {
            win = 0;
        }
        else
        {
            win = 1;
        }
        for(int j =0; j< N; j++)
            {
                if(ListeCombat[2*i+win]>=P)
                nouveau_parent[i][j] =  enfant[ListeCombat[2*i+win]%P][j];
                else
                nouveau_parent[i][j] =  parent[ListeCombat[2*i+win]][j];
            }
    }
    
    for(int i =0; i<P; i++)
        for(int j=0; j<N; j++)
            parent[i][j] = nouveau_parent[i][j];

    for(int i = 0; i < P; i++)
    {
       delete nouveau_parent[i];
    }
    delete nouveau_parent;
    
    
    
}