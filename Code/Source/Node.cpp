/* 
 * File:   Node.cpp
 * Author: Julien Lemay & Alexandre Lessard
 * Date: 20/11/15
 */

// Include

#include "../Header/Node.hpp"

int Node::nbNodes = 0; // Initialisation du nombre de noeuds a 0

/**
 * Constructeur de Node
 */
Node::Node(void)
{
    ID = nbNodes++; // Donne le ID et augmente la valeur du nombre de noeuds
}

Node::Node(int &externalID)
{
    ID = externalID++; // Donne le ID et augmente la valeur du nombre de noeuds
}

/**
 * Destructeur de Node
 */
Node::~Node(void)
{
    
}

/**
 * Recherche sequentielle pour trouver si un noeud est dans la liste des voisins
 * @param id ID du voisin a rechercher
 * @return L'index du voisin ou -1 si non present 
 */
int Node::SearchID(int id)
{
    for (int i = 0; i < nbNeighbors; i++) //linkedNeighbors.size()
    {
        if(linkedNeighbors[i] == id)
        {
            return i;
        }
    }
    
    return -1;
}

/**
 * Retourne le ID du noeud
 * @return ID du noeud
 */
int Node::GetID(void)
{
    return ID;
}

/**
 * Retourne le nombre de voisins
 * @return Le nombre de voisins
 */
int Node::GetNbNeighbors(void)
{
    return nbNeighbors;
}

/**
 * Ajoute/modifie/efface un noeud de la liste des voisins
 * @param n Le noeud a utiliser
 * @param weight Le poids de la connection (-1 = deconnecte)
 */
void Node::AddConnection(Node &n, int weight)
{
    //on cherche le noeud dans la liste des voisins
    int id = SearchID(n.GetID());
    
    //Si le noeud n'est pas dans la liste des voisins et le poids >= 0
    //On ajoute le noeud dans la liste des voisins ave le poids
    if(id <= -1 && weight > -1)
    {
        linkedNeighbors.push_back(n.GetID());
        linkedWeights.push_back(weight);
        nbNeighbors++;
    }
    //Si le noeud est dans la liste des voisins et le poids est -1 ( deconnecte))
    //On enleve le noeud de la liste des voisins et des poids voisins
    else if(id > -1 && weight <= -1)
    {
        linkedNeighbors.erase(linkedNeighbors.begin()+id);
        linkedWeights.erase(linkedWeights.begin()+id);
        nbNeighbors--;
    }
    
    //Si le noeud est dans la liste des voisins et le poid >=0
    //On ajuste le poids avec le voisins
    else if(id > -1 && weight > -1)
    {
        linkedWeights[id] = weight;
    }
}

/**
 * (STATIC) Connecte 2 noeuds de façon non oriente et non pondere
 * @param n1 Noeud a connecter #1
 * @param n2 Noeud a connecter #2
 */
void Node::Connect(Node &n1, Node &n2)
{
    Connect(n1, n2, 1, 1); //Non oriente et Non pondere
}

/**
 * (STATIC) Connecte 2 noeuds de façon non oriente et pondere
 * @param n1 Noeud a connecter #1
 * @param n2 Noeud a connecter #2
 * @param weight Poids de la connection entre 1 et 2
 */
void Node::Connect(Node &n1, Node &n2, int weight)
{
    Connect(n1, n2, weight, weight); //Non oriente et pondere
}
 
/**
 * (STATIC) Connecte 2 noeuds de façon oriente et pondere
 * @param n1 Noeud a connecter #1
 * @param n2 Noeud a connecter #2
 * @param weightN1ToN2 Poids de la connection de #1 a #2
 * @param weightN2ToN1 Poids de la connection de #2 a #1
 */
void Node::Connect(Node &n1, Node &n2, int weightN1ToN2, int weightN2ToN1)
{
    n1.AddConnection(n2, weightN1ToN2); //Oriente et pondere 
    n2.AddConnection(n1, weightN2ToN1);
}

/**
 * Permet d'imprimer les connexions des noeuds
 */
void Node::PrintConnection(void)
{
    cout << "(" << ID << ")" << endl;
    
    for (int i = 0; i < nbNeighbors ; i++)
    {
        if(linkedNeighbors[i] != ID)
        {
            cout << "|" << endl << "|---" << linkedWeights[i];
            cout << "-->(" << linkedNeighbors[i] << ")" << endl;     
        }
    }
    cout << endl;
}

bool Node::GetVisited(void)
{
    return isVisited;
}

void Node::SetVisited(bool state)
{
    isVisited=state;
}

int Node::GetNeighbor(int index)
{
    return linkedNeighbors[index];
}

int Node::GetWeight(int index)
{
    return linkedWeights[index];
}

/**
 * Tri les voisins du Noeud par ordre croissant de poids
 */
void Node::SortNeighborsWeight(void)
{
    int tmp1, tmp2, j;
    for(int i=1; i<nbNeighbors; i++)
    {
        tmp1 = linkedWeights[i];
        tmp2 = linkedNeighbors[i];
        j=i;
        while(j>0&&linkedWeights[j-1]>tmp1)
        {
            linkedWeights[j] = linkedWeights[j-1];
            linkedNeighbors[j] = linkedNeighbors[j-1];
            j--;
        }
        linkedWeights[j] = tmp1;
        linkedNeighbors[j] = tmp2;
    }
}

/**
 * Initialise le compteur pour identifier les noeuds
 * @param id
 */
void Node::NodeExternalIDInit(int& id)
{
    id = 0;
}

int Node::GetNbConflict(void)
{
    return nbConflict;
}

void Node::SetNbConflict(int nb)
{
    nbConflict = nb;
}
    
bool Node::GetIsQueen(void)
{
    return isQueen;
}

void Node::SetIsQueen(bool state)
{
    isQueen = state;
}
