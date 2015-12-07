/*
 * Nom : generalFunctions.cpp
 * Auteur : Julien Lemay & Alexandre Lessard
 * Description : Contient plusieurs fonctions nÃ©cessaire au deroulement du
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

/**
 * Genere des chromosomes au hasard contenant des données entre 1 et N-1 sans répétition dans un gène
 * @param tableau tableau à utiliser
 * @param P Nombre de chromosomes
 * @param N Taille d'un chromosome
 * @return temps de calcul
 */
long GenererChromosomes(int **tableau, int P, int N)
{
    long tmpCalcul=0;
    // Definition des variables
    int tmp, rnd;
    // Debut du programme
    for(int i = 0; i < P; i++)
    {
        for(int j = 0; j < N; j++)
        {
            tmpCalcul++;
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
    return tmpCalcul;
}

//void xChange (int index1, int index2, int *matrix)
//{
//    // Definition des variables
//    int temp; // Variable temporaire
//    
//    // Debut du program
//    
//    temp = matrix[index1];
//    matrix[index1] = matrix[index2];
//    matrix[index2] = temp;
//}
//
//void shiftLeft(int N, int *matrix)
//{
//    // DÃ©claration des variables
//    int temp; // variable temporaire.
//    
//    // DÃ©but du programme
//    
//    temp = matrix[0];
//    for (int i = 0; i < N-1; i++)
//    {
//        matrix[i] = matrix[i+1];
//    }
//    matrix[N-1] = temp;
//}
//
//void shiftRight(int N, int *matrix)
//{
//    // DÃ©claration des variables
//    int temp; // variable temporaire.
//    
//    // DÃ©but du programme
//    
//    temp = matrix[N-1];
//    for (int i = N-1; i >= 0; i--)
//    {
//        matrix[i] = matrix[i-1];
//    }
//    matrix[0] = temp;
//}

/**
 * Remélange les données de 2 parents
 * @param N Taille des gènes
 * @param P Nombre de gènes
 * @param parent Liste des parents
 * @param enfant Liste des enfants
 * @return temps de calcul
 */
unsigned long long Recombinaison(int N, int P, int **parent, int **enfant)
{
    long tmpCalcul = 0;
    int listRecomb[N];
    int tmp, rnd, nbRecomb;
    int * PosToChange;
    
    
    for(int i = 0; i < N; i++)
        listRecomb[i] = i/2;
    
    int ListeParent[P];
    
    for(int j = 0; j < P; j++)//Melange index parent
    {
        ListeParent[j] = j;
    }

    for(int j = P-1; j >= 0; j--) //genere couple parent au hasard
    {
        rnd = rand()%(j+1);
        tmp = ListeParent[j];
        ListeParent[j] = ListeParent[rnd];
        ListeParent[rnd] = tmp;
    }
    
    for(int j = 0; j < P; j++) // Creer enfants a  partir de parents
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
        
            for(int i =0; i<nbRecomb*2; i++) // établissement des positions a intervertir
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
                    tmpCalcul++;
                }
            }

            delete PosToChange;
        }
    }
    return tmpCalcul;
}

/**
 * Mute les gènes en intervertissant 2 positions au hasard
 * @param N Taille d'un chromosome
 * @param P nombre de chromosomes
 * @param enfant Liste des enfants
 * @return temps de calcul
 */
unsigned long long Mutation(int N, int P, int **enfant)
{
    unsigned long long tmpCalcul = 0;
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
                tmpCalcul++;
            }
        }
    }
    return tmpCalcul;
}

/**
 * Élimine la moitié des parents et enfants en comparant 2 chromosomes à la fois
 * @param N Taille d'un chromosome
 * @param P Nombre de chromosomes parent
 * @param parent Liste des parents
 * @param enfant Liste des enfants
 * @param board Échiquier
 * @return temps de calcul
 */
unsigned long long Combat(int N, int P, int **parent, int **enfant, ChessBoard *board)
{
    long tmpCalcul = 0;
    int **nouveau_parent = new int*[P];
    for(int i = 0; i < P; i++)
    {
        nouveau_parent[i] = new int[N];
    }
    
    int ListeCombat[2 * P];
    int rnd, tmp, win;
    int combatant[2];
    
    for(int j = 0; j < 2*P; j++)//MÃ©langÃ© index parent
    {
        ListeCombat[j] = j;
    }

    for(int j = 2*P-1; j >= 0; j--) //GÃ©nÃ¨re couple parent au hasard
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
        {
            parent[i][j] = nouveau_parent[i][j];
            tmpCalcul++;
        }

    for(int i = 0; i < P; i++)
    {
       delete nouveau_parent[i];
    }
    delete nouveau_parent;
    
    return tmpCalcul;
    
}