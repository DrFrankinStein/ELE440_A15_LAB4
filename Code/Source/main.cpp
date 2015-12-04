/* 
 * File:   main.cpp
 * Author: Julien
 *
 * Created on 20 novembre 2015, 09:56
 */

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "../Header/ChessBoard.hpp"
#include "../Header/GeneralFunctions.hpp"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
    srand(time(NULL));
    int N = 100;
    ChessBoard c(N);
    
    
    int Z, min=N*N;
    long gen = 0;
//    
//    int list[5] = {4,1,3,0,2};
//    
//    Z = c.CalculateFitness(list);
//    
//    c.DrawTileFitness();
//    cout << Z;
    
    //int N = 8;
    int P = 10;
    
    int **chromosomes = new int*[P];
    int **enfant = new int*[P];
    for(int i = 0; i < P; i++)
    {
        chromosomes[i] = new int[N];
        enfant[i] = new int[N];
    }
        
    GenererChromosomes(chromosomes, P, N);
    
    while(min!=0)
    {
        Recombinaison(N, P, chromosomes, enfant);
        Mutation(N, P, enfant);
        Combat(N, P, chromosomes, enfant, &c);
        for(int i = 0; i<P && min !=0; i++)
        {
            Z = c.CalculateFitness(chromosomes[i]);
            if(Z<min)
                min = Z; 
        }
        //cout << "min=" << min << "gen="<< gen << "\r";
        if(0==(gen%50) || min==0)
            printf("gen = %li min = %i \r", gen, min);
        gen++;
    }
    cout << endl;
    cout<<"parent"<<endl;
    for(int i =0; i<P ; i++)
    {
        for (int j = 0; j<N; j++)
        {
            cout << chromosomes[i][j] << "\t";
        }
        Z = c.CalculateFitness(chromosomes[i]);
        cout << "\t= " << Z << endl;
    }
//    
//    Recombinaison(N, P, chromosomes, enfant);
//    
////    cout<<"enfant"<<endl;
////    for(int i =0; i<P ; i++)
////    {
////        for (int j = 0; j<N; j++)
////        {
////            cout << enfant[i][j] << "\t";
////        }
////        Z = c.CalculateFitness(enfant[i]);
////        cout << "\t= " << Z << endl;
////    }
//    
//    Mutation(N, P, enfant);
//    
//    cout<<"enfant muter"<<endl;
//    for(int i =0; i<P ; i++)
//    {
//        for (int j = 0; j<N; j++)
//        {
//            cout << enfant[i][j] << "\t";
//        }
//        Z = c.CalculateFitness(enfant[i]);
//        cout << "\t= " << Z << endl;
//    }
//    
//    Combat(N, P, chromosomes, enfant, &c);
//    
//    cout<<"parent 2"<<endl;
//    for(int i =0; i<P ; i++)
//    {
//        for (int j = 0; j<N; j++)
//        {
//            cout << chromosomes[i][j] << "\t";
//        }
//        Z = c.CalculateFitness(chromosomes[i]);
//        cout << "\t= " << Z << endl;
//    }
//    
//    Recombinaison(N, P, chromosomes, enfant);
//    
////    cout<<"enfant"<<endl;
////    for(int i =0; i<P ; i++)
////    {
////        for (int j = 0; j<N; j++)
////        {
////            cout << enfant[i][j] << "\t";
////        }
////        Z = c.CalculateFitness(enfant[i]);
////        cout << "\t= " << Z << endl;
////    }
//    
//    Mutation(N, P, enfant);
//    
//    cout<<"enfant muter 2"<<endl;
//    for(int i =0; i<P ; i++)
//    {
//        for (int j = 0; j<N; j++)
//        {
//            cout << enfant[i][j] << "\t";
//        }
//        Z = c.CalculateFitness(enfant[i]);
//        cout << "\t= " << Z << endl;
//    }
//    
//    Combat(N, P, chromosomes, enfant, &c);
//    
//    cout<<"parent 3"<<endl;
//    for(int i =0; i<P ; i++)
//    {
//        for (int j = 0; j<N; j++)
//        {
//            cout << chromosomes[i][j] << "\t";
//        }
//        Z = c.CalculateFitness(chromosomes[i]);
//        cout << "\t= " << Z << endl;
//    }
//    
//     Recombinaison(N, P, chromosomes, enfant);
//    
////    cout<<"enfant"<<endl;
////    for(int i =0; i<P ; i++)
////    {
////        for (int j = 0; j<N; j++)
////        {
////            cout << enfant[i][j] << "\t";
////        }
////        Z = c.CalculateFitness(enfant[i]);
////        cout << "\t= " << Z << endl;
////    }
//    
//    Mutation(N, P, enfant);
//    
//    cout<<"enfant muter 3"<<endl;
//    for(int i =0; i<P ; i++)
//    {
//        for (int j = 0; j<N; j++)
//        {
//            cout << enfant[i][j] << "\t";
//        }
//        Z = c.CalculateFitness(enfant[i]);
//        cout << "\t= " << Z << endl;
//    }
//    
//    Combat(N, P, chromosomes, enfant, &c);
//    
//    cout<<"parent 4"<<endl;
//    for(int i =0; i<P ; i++)
//    {
//        for (int j = 0; j<N; j++)
//        {
//            cout << chromosomes[i][j] << "\t";
//        }
//        Z = c.CalculateFitness(chromosomes[i]);
//        cout << "\t= " << Z << endl;
//    }
//    
    return 0;
}

