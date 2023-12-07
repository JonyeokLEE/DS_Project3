#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
	m_Mat = new int* [size+1];
	for (int i = 0; i <= size; i++) {
		m_Mat[i] = new int[size+1];
	}
}

MatrixGraph::~MatrixGraph()
{
	for (int i = 0; i <= m_Size; i++)
	{
		delete[] m_Mat[i];
	}
	delete[] m_Mat;
}

int MatrixGraph::getLength(int from, int to, char option)
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


void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m, char option)
{	
	if (option == 'Y') getAdjacentEdgesDirect(vertex, m);
	else if (option == 'N') getAdjacentEdgesUnDirect(vertex, m);
	else return;
}

void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)
{
	for (int i = 1; i <= m_Size; i++)
	{
		if (m_Mat[vertex][i] != 0)
		{
			m->insert(map<int, int>::value_type(i, m_Mat[vertex][i]));
		}
	}
}

void MatrixGraph::getAdjacentEdgesUnDirect(int vertex, map<int, int>* m)
{
	for (int i = 1; i <= m_Size; i++)
	{
		if (m_Mat[vertex][i] != 0)
		{
			m->insert(map<int, int>::value_type(i, m_Mat[vertex][i]));
		}
	}
	for (int i = 1; i <= m_Size; i++)
	{
		if (m_Mat[i][vertex] != 0)
		{
			m->insert(map<int, int>::value_type(i, m_Mat[i][vertex]));
		}
	}
}

void MatrixGraph::getIncomingEdges(int vertex, map<int, int>* m)
{
	for (int i = 1; i <= m_Size; i++)
	{
		if (m_Mat[i][vertex] != 0)
		{
			m->insert(map<int, int>::value_type(i, m_Mat[i][vertex]));
		}
	}
}

void MatrixGraph::insertEdge(int from, int to, int weight)	
{
	m_Mat[from][to] = weight;
}

bool MatrixGraph::printGraph(ofstream *fout)	
{
	if (m_Size == 0) return false;
	*fout << "======== PRINT ========" << endl;
	*fout << "  " << setw(4);
	for (int j = 1; j <= m_Size; j++)
	{
		*fout << setw(2)<<"[" << j << "]";
	}*fout << endl;
	for (int i = 1; i <= m_Size; i++)
	{
		*fout << "[" << i << "] ";
		for (int j = 1; j <= m_Size; j++)
		{
			*fout << m_Mat[i][j] << setw(4);
		}
		*fout << endl<<setw(0);
	}
	*fout << "=====================" << endl;
	return true;
}

