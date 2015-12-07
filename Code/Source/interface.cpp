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
#include "../Header/ChessBoard.hpp"

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
    int maxG; // Nombre maximum de générations
    long currentG=0; //Nombre actuel de générations
    int minFit; //Minimum de fitness
    int tmpFit; //Fitness temporaire calculé
    
    //Probabilité
    float probRecomb1 = 2/(float)N ; //Valeurs hardcodés plus tôt
    float probRecombAll = (float)(N-2)/(float)N ; //Valeurs hardcodés plus tôt
    float probMut = 0.25 * 1/2; 
    
    unsigned long long tmpCalcul = 0;
    int nbSol = 0;
    
    int ** chromosomes;
    int ** enfant;
    
    // Initialisation des variables
    
    // Debut du programme
    cout << "ELE440 - LABORATOIRE 4" << endl;
    cout << "Algorithmes genetiques" << endl << endl;
    
    do
    {
        cout << "(1) Generer un echiquier aleatoirement" << endl;
        cout << "(2) Generer un echiquier a partir d'un fichier" << endl;
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
    
    enfant = new int*[P];
    for(int i = 0; i < P; i++)
        enfant[i] = new int[N];
    
    cout << "Nombre maximum de generations? : ";
    scanf("%d",&maxG);
        
    minFit = N*N;
    ChessBoard c(N);
    
    //Calcul des générations
    while(minFit!=0 && currentG <= maxG)
    {
        tmpCalcul+=Recombinaison(N, P, chromosomes, enfant);
        tmpCalcul+=Mutation(N, P, enfant);
        tmpCalcul+=Combat(N, P, chromosomes, enfant, &c);
        for(int i = 0; i<P && minFit !=0; i++)
        {
            tmpFit = c.CalculateFitness(chromosomes[i], tmpCalcul);
            if(tmpFit<minFit)
            {
                minFit = tmpFit; 
                tmpCalcul++;
            }
        }
        if(0==(currentG%10) || minFit==0)
            printf("G = %li minFit = %i \r", currentG, minFit);
        currentG++;
    }
    
    cout << "Nombre de reines : " << N << endl;
    cout << "Taille de la population : " << P << endl;
    cout << "Nombre de generation : " << currentG-1 << endl;
    cout << "Probabilite de recombinaison de chaque type : " << probRecomb1 << endl;
    cout << "Probabilite de recombinaison totale : " << probRecombAll << endl;
    cout << "Probabilite de mutation : " << probMut << endl;
    cout << "Meilleur fitness obtenu : " << minFit << endl;
    cout << "Temps de calcul : " << tmpCalcul << endl << endl;
    
    for(int i =0; i<P ; i++)
    {
        tmpFit = c.CalculateFitness(chromosomes[i]);
        if(tmpFit==0)
        {     
            nbSol++;
        }   
    }
    
    cout << "Nombre de solutions trouvees : " << nbSol << endl;
    cout << "Solutions trouvees : " << endl;
    
    for(int i =0; i<P ; i++)
    {
        tmpFit = c.CalculateFitness(chromosomes[i]);
        if(tmpFit==0)
        {     
            for (int j = 0; j<N; j++)
            {
                cout << chromosomes[i][j] << "\t";
            }
            cout << endl << endl;
            c.DrawQueens(chromosomes[i]);
            cout << endl;
        }
    }
    
    cout << endl;

    for(int i = 0; i<P; i++)
    {
        delete chromosomes[i];
        delete enfant[i];
    }
    
    delete chromosomes;
    delete enfant;
    
}