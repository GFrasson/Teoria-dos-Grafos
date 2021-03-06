#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node)
{

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {

        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

// Getters
int Graph::getOrder()
{

    return this->order;
}
int Graph::getNumberEdges()
{

    return this->number_edges;
}
//Function that verifies if the graph is directed
bool Graph::getDirected()
{

    return this->directed;
}
//Function that verifies if the graph is weighted at the edges
bool Graph::getWeightedEdge()
{

    return this->weighted_edge;
}

//Function that verifies if the graph is weighted at the nodes
bool Graph::getWeightedNode()
{

    return this->weighted_node;
}


Node *Graph::getFirstNode()
{

    return this->first_node;
}

Node *Graph::getLastNode()
{

    return this->last_node;
}

// Setters
void Graph::setFirstNode(Node *node)
{
    this->first_node = node;
}

void Graph::setLastNode(Node *node)
{
    this->last_node = node;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/

// Precisamos conhecer como funciona o arquivo de leitura
void Graph::insertNode(int id)
{
    if (getFirstNode() != nullptr)
    {
        if (searchNode(id))
        {
            cerr << "Erro: N?? " << id << " j?? foi inserido" << endl;
        }
        else
        {
            Node *node = new Node(id);
            getLastNode()->setNextNode(node);
            setLastNode(node);
            this->order++;
        }
    }
    else
    {
        Node *node = new Node(id);
        setFirstNode(node);
        setLastNode(node);
        this->order++;
    }
}

void Graph::insertEdge(int id, int target_id, float weight)
{
    Node *node = getNode(id);
    Node *targetNode = getNode(target_id);

    if (node == nullptr)
    {
        insertNode(id);
        node = getNode(id);
    }

    if (targetNode == nullptr)
    {
        insertNode(target_id);
        targetNode = getNode(target_id);
    }

    if (!node->searchEdge(target_id))
    {
        if (getDirected())
        {
            node->incrementOutDegree();
            targetNode->incrementInDegree();
            node->insertEdge(target_id, weight);
        }
        else
        {
            node->incrementInDegree();
            node->insertEdge(target_id, weight);
            targetNode->incrementInDegree();
            targetNode->insertEdge(id, weight);
        }

        number_edges += 1;
    }

    // Mostrar Erro caso encontre a aresta
}

void Graph::removeNode(int id)
{
    if (!searchNode(id))
    {
        cerr << "Erro: N?? " << id << " n??o foi encontrado" << endl;
    }
    else
    {
        Node *currentNode = nullptr;
        Node *previousNode = nullptr;

        for (currentNode = getFirstNode(); currentNode->getId() != id; currentNode = currentNode->getNextNode())
        {
            previousNode = currentNode;
        }

        if (previousNode != nullptr)
        {
            previousNode->setNextNode(currentNode->getNextNode());
        }
        else
        {
            setFirstNode(currentNode->getNextNode());
        }

        if (currentNode->getNextNode() == nullptr)
        {
            setLastNode(previousNode);
        }

        currentNode->removeAllEdges();
        delete currentNode;
    }
}

bool Graph::searchNode(int id)
{
    if (getFirstNode() != nullptr)
    {
        for (Node *aux = getFirstNode(); aux != nullptr; aux->getNextNode())
        {
            if (aux->getId() == id)
            {
                return true;
            }
        }
    }

    return false;
}

Node *Graph::getNode(int id)
{
    if (getFirstNode() != nullptr)
    {
        for (Node *aux = getFirstNode(); aux != nullptr; aux->getNextNode())
        {
            if (aux->getId() == id)
            {
                return aux;
            }
        }
    }

    return nullptr;
}

//Function that prints a set of edges belongs breadth tree

void Graph::breadthFirstSearch(ofstream &output_file)
{

}



float Graph::floydMarshall(int idSource, int idTarget)
{

}



float Graph::dijkstra(int idSource, int idTarget)
{

}

//function that prints a topological sorting
void Graph::topologicalSorting()
{

}

void Graph::breadthFirstSearch(ofstream& output_file)
{

}

Graph* Graph::getVertexInduced(vector<int> listIdNodes)
{
    Graph *subgraph = new Graph(0, this->getDirected(), this->getWeightedEdge(), this->getWeightedNode());
    int listSize = listIdNodes.size();

    for (int i = 0; i < listSize; i++)
    {
        subgraph->insertNode(listIdNodes[i]);

        Node *node = getNode(listIdNodes[i]);

        if (node != nullptr){
            if(i+1 < listIdNodes.size()){
                int j = i;
                for (Node *auxNode = getNode(listIdNodes[j++]); auxNode != nullptr; auxNode = getNode(listIdNodes[j++])){
                    for (Edge *auxEdge = auxNode->getFirstEdge(); auxEdge != nullptr; auxEdge = auxEdge->getNextEdge()){
                        if(j == listIdNodes.size())
                            break;

                        if(node->getId() == auxEdge->getTargetId()){
                            node->insertEdge(auxNode, auxEdge->getWeight());
                            break;
                        }
                    }
                }
            }
        }
    }


    return subgraph;


}

Graph* Graph::agmKuskal()
{

}

Graph* Graph::agmPrim()
{

}
