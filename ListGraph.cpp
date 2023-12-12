#include "ListGraph.h"
#include <iostream>
#include <utility>

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_List = new map<int, int>[size+1];
	kw_graph = new vector<int>[size+1];
}

ListGraph::~ListGraph()	
{
	delete[] m_List;
	delete[] kw_graph;
}

int ListGraph::getLength(int from, int to, char option)
{
	if (from == to) return 0;
	map<int, int> info;
	bool connected = false;
	getAdjacentEdges(from, &info, option);

	int length = 0;
	for (auto itr = info.begin(); itr != info.end(); itr++)
	{
		if (to == itr->first)
		{
			length = itr->second;
			if (from == to && length > 0)length = 0;
			connected = true;
		}
	}
	if (connected) return length;
	if (!connected) return 800000000; //disconnect -> return the largest number
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m, char option)
{
	if (option == 'Y') //direct
	{
		getAdjacentEdgesDirect(vertex, m);
	}
	else if (option == 'N') //undirect
	{
		getAdjacentEdgesUnDirect(vertex, m);
	}
	else return;
}

void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)	//Definition of getAdjacentEdges(Directed graph)
{
	m->insert(m_List[vertex].begin(), m_List[vertex].end()); //get vertex's adjacency edges
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
	//get all edges connected with vertex
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
	} //get incoming edges
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
		*fout << "[" << i << "]";
		for (auto mi = m_List[i].begin();mi!=m_List[i].end();mi++)
		{
			*fout << "-> (" << mi->first << "," << mi->second << ")";
		}
		*fout << endl;
	}
	*fout << "=====================" << endl << endl;
	
	return true;
}

void ListGraph::getkw_graph(vector<int>& kgraph, int i)
{
	for (int j = 0; j < kw_graph[i].size(); j++)
	{
		kgraph.push_back(kw_graph[i][j]);
	}
}

void ListGraph::setkw_graph()
{
	map<int, int> relation;

	for (int i = 1; i <= m_Size; i++)
	{
		getAdjacentEdgesUnDirect(i, &relation);
		for (auto itr = relation.begin(); itr != relation.end(); itr++)
		{
			kw_graph[i].push_back(itr->first);
		}
		sort(kw_graph[i].begin(), kw_graph[i].end());
		relation.clear();
	}
}

