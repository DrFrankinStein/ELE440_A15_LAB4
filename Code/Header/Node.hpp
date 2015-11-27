/* 
 * File:   Node.hpp
 * Author: Julien Lemay & Alexandre Lessard
 * Date: 20/11/15
 */

#ifndef _NODE_HPP
#define	_NODE_HPP

// Include

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Classe qui sert a creer et connecter des noeuds
 */
class Node
{
public :
    Node(void);
    Node(int &externalID);
    ~Node(void);
    
    int GetID(void);
    int SearchID(int id);
    int GetNbNeighbors(void);
    bool GetVisited(void);
    void SetVisited(bool state);
    int GetNeighbor(int index);
    int GetWeight(int index);
    void SortNeighborsWeight(void);
    
    void AddConnection(Node &n, int weight);
    
    void PrintConnection(void);
    
    static void Connect(Node &n1, Node &n2);
    static void Connect(Node &n1, Node &n2, int weight);
    static void Connect(Node &n1, Node &n2, int weightN1ToN2, int weightN2ToN1);
    static void NodeExternalIDInit(int &id);
    
private:
    static int nbNodes; //Nombre de noeuds crees
    int ID; //Identifiant du noeud
    bool isVisited = false; 
    int nbNeighbors = 0; //Nombre de voisins du noeud
    
    vector<int> linkedNeighbors; // Liste des voisins (index)
    vector<int> linkedWeights; // Liste des poids des connections avec les voisins
};

#endif //_NODE_HPP