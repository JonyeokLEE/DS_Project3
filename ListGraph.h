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

	int getLength(int from, int to, bool directed);
	void getAdjacentEdges(int vertex, map<int, int>* m, bool directed);
	void getAdjacentEdgesDirect(int vertex, map<int, int>* m);
	void getAdjacentEdgesUnDirect(int vertex, map<int, int>* m);
	void insertEdge(int from, int to, int weight);	
	bool printGraph(ofstream *fout);

};

#endif