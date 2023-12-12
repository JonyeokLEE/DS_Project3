#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
#include <map>
#include <set>
#include <math.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <iomanip>
using namespace std;

class Graph{	
protected:
	bool m_Type;
	int m_Size;

public:
	Graph(bool type, int size);
	virtual ~Graph();

	bool getType();	
	int getSize();

	virtual int getLength(int from, int to, char option) = 0; //get weight
	virtual void getAdjacentEdges(int vertex, map<int, int>* m, char option) = 0;
	virtual void getAdjacentEdgesDirect(int vertex, map<int, int>* m) = 0;
	virtual void getAdjacentEdgesUnDirect(int vertex, map<int, int>* m) = 0;
	virtual void getIncomingEdges(int vertex, map<int, int>* m) = 0; //get edges
	virtual void insertEdge(int from, int to, int weight) = 0; //LOAD			
	virtual	bool printGraph(ofstream *fout) = 0; //PRINT
	virtual void getkw_graph(vector<int>& kgraph, int i) = 0; //get kwgraph
	virtual void setkw_graph() = 0; //set kwgraph
};

#endif
