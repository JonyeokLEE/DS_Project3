#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <map>
#include "Graph.h"

class MatrixGraph : public Graph{	
private:
	int** m_Mat;

public:
	MatrixGraph(bool type, int size);
	~MatrixGraph();
		
	int getLength(int from, int to, bool directed);
	void getAdjacentEdges(int vertex, map<int, int>* m, bool directed);	
	void getAdjacentEdgesDirect(int vertex, map<int, int>* m);
	void getAdjacentEdgesUnDirect(int vertex, map<int, int>* m);
	void insertEdge(int from, int to, int weight);	
	bool printGraph(ofstream *fout);

};

#endif