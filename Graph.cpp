#include "Graph.h"

Graph::Graph(bool type, int size) //set Type and size
{
	m_Type = type;
	m_Size = size;
}

Graph::~Graph()	
{

}


bool Graph::getType(){return m_Type;}	
int Graph::getSize(){return m_Size;}
