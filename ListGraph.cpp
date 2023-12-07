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

int ListGraph::getLength(int from, int to, char option)
{
	map<int, int> info;
	bool connected = false;
	getAdjacentEdges(from, &info, option);

	int length = 0;
	for (auto itr = info.begin(); itr != info.end(); itr++)
	{
		if (to == itr->first)
		{
			length = itr->second;
			connected = true;
		}
	}
	if (connected) return length;
	if (!connected) length = 800000000;
	if (!connected && from == to)length = 0;
	return length;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m, char option)
{
	if (option == 'Y')
	{
		getAdjacentEdgesDirect(vertex, m);
	}
	else if (option == 'N')
	{
		getAdjacentEdgesUnDirect(vertex, m);
	}
	else return;
}

void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)	//Definition of getAdjacentEdges(Directed graph)
{
	m->insert(m_List[vertex].begin(), m_List[vertex].end());
}

void ListGraph::getAdjacentEdgesUnDirect(int vertex, map<int, int>* m)
{
	for (int i = 1; i <= m_Size; i++)
	{
		if (i == vertex)
		{
			for (auto itr = m_List[vertex].begin(); itr != m_List[vertex].end(); itr++)
			{
				m->insert(map<int, int>::value_type(itr->first, itr->second));
			}
		}
		else
		{
			for (auto itr = m_List[i].begin(); itr != m_List[i].end(); itr++)
			{
				if (itr->first == vertex)
				{
					m->insert(map<int, int>::value_type(i, itr->second));
				}
			}
		}
	}
}

void ListGraph::getIncomingEdges(int vertex, map<int, int>* m)
{
	for (int i = 1; i <= m_Size; i++)
	{
		for (auto itr = m_List[i].begin(); itr != m_List[i].end(); itr++)
		{
			if (itr->first == vertex)
			{
				m->insert(map<int, int>::value_type(i, itr->second));
			}
		}
	}
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

