#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph{	
private:
	map < int, int >* m_List;
	vector<int>* kw_graph;
	
public:	
	ListGraph(bool type, int size);
	~ListGraph();

	int getLength(int from, int to, char option);
	void getAdjacentEdges(int vertex, map<int, int>* m, char option);
	void getAdjacentEdgesDirect(int vertex, map<int, int>* m);
	void getAdjacentEdgesUnDirect(int vertex, map<int, int>* m);
	void getIncomingEdges(int vertex, map<int, int>* m);
	void insertEdge(int from, int to, int weight);	
	bool printGraph(ofstream *fout);
	void getkw_graph(vector<int>& kgraph, int i);
	//void getkw_graph(vector<int>*& kgraph);
	void setkw_graph();
};

#endif