#include "ListGraph.h"
#include <iostream>
#include <utility>

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_List = new map<int, int>[size+1];
	kw_graph = nullptr;
	
}

ListGraph::~ListGraph()	
{
	
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)	 //Definition of getAdjacentEdges(No Direction == Undirected)
{
	
}

void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)	//Definition of getAdjacentEdges(Directed graph)
{
	
}

void ListGraph::insertEdge(int from, int to, int weight) //Definition of insertEdge
{
	m_List[from].insert(map<int, int>::value_type(to,weight));
}

bool ListGraph::printGraph(ofstream *fout)	//Definition of print Graph
{
	if (m_Size == 0) return false;

	*fout << "======== PRINT ========" << endl;
	for (int i = 1; i <= m_Size; i++)
	{
		if (m_List[i].size() == 0) return false;
		*fout << "[" << i << "]";
		for (auto mi = m_List[i].begin();mi!=m_List[i].end();mi++)
		{
			*fout << "-> (" << mi->first << "," << mi->second << ")";
		}
		*fout << endl;
	}
	*fout << "=====================" << endl;
	return true;
}