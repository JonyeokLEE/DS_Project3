#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
	m_Mat = new int* [size];
	for (int i = 0; i < size; i++) {
		m_Mat[i] = new int[size];
	}
}

MatrixGraph::~MatrixGraph()
{
	for (int i = 0; i < m_Size; i++)
	{
		delete[] m_Mat[i];
	}
	delete[] m_Mat;
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{	

}

void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)
{
	
}

void MatrixGraph::insertEdge(int from, int to, int weight)	
{
	m_Mat[from - 1][to - 1] = weight;
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
	for (int i = 0; i < m_Size; i++)
	{
		*fout << "[" << i+1 << "] ";
		for (int j = 0; j < m_Size; j++)
		{
			*fout << m_Mat[i][j] << setw(4);
		}
		*fout << endl<<setw(0);
	}
	*fout << "=====================" << endl;
	return true;
}
