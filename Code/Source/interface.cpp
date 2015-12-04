/*
 * Nom : interface.cpp
 * Auteur : Julien Lemay & Alexandre Lessard
 * Description : Affiche les différentes options offertes à l'usager.
 * Date : 20/11/15
 */

// Include

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <climits>
#include <ctime>

#include "../Header/FileTools.hpp" // LoadFromFile
#include "../Header/GeneralFunctions.hpp" // GenererChromosomes

using namespace std;

/*
 * Description : Debuter le programme principale.
 */

void start(void)
{
    // Definition des variables
    srand(time(NULL));
    int option;
    int N; // Nombre de reines
    int P; // Nombre de Chromosomes
    int ** chromosomes;
    
    // Initialisation des variables
    
    // Debut du programme
    cout << "ELE440 - LABORATOIRE 4" << endl;
    cout << "Algorithmes genetiques" << endl << endl;
    
    do
    {
        cout << "(1) Generer une grille aleatoirement" << endl;
        cout << "(2) Générer une grille a partir d'un fichier" << endl;
        cout << "Choix : ";
        scanf("%d",&option);
    }while(option < 1 || option > 2);
    
    switch(option)
    {
        case 1:
        {
            do
            {
                cout << "Combien de reines a placer? : ";
                scanf("%d",&N);
            }while(N < 4);
            
            do
            {
                cout << "Combien de chromosomes? : ";
                scanf("%d",&P);
            }while(P < 1);
            
            chromosomes = new int*[P];
            for(int i = 0; i < P; i++)
                chromosomes[i] = new int[N];

            GenererChromosomes(chromosomes, P, N);
            
        }break;
        
        case 2:
        {
            char fileName[PATH_MAX];
            do
            {
                printf("Adresse du fichier : \n");
                scanf("%s",fileName);
                chromosomes = LoadFromFile(fileName, P, N);
            }
            while(N<0);
        }break;
        
    }
    
    // Générer les chromosomes
    
    //int ** chromosomes;
    
    
    for(int i = 0; i < P; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << chromosomes[i][j] << " - ";
        }
        cout << endl;
    }
}