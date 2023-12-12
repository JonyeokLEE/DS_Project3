#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"




bool BFS(Graph* graph, char option, int vertex, ofstream* fout);     
bool DFS(Graph* graph, char option,  int vertex, ofstream* fout);

void InsertionSort(vector<pair<int, pair<int, int>>>& E, int low, int high);
void QuickSort(vector<pair<int,pair<int, int>>>& E, int low, int high);
int Find(int* prev, int tofind);
void Union(int* prev, int a, int b);
bool isUnion(int* prev, int a, int b);
bool Kruskal(Graph* graph, ofstream* fout);
bool Dijkstra(Graph* graph, char option, int vertex, ofstream *fout);    //Dijkstra
bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex, ofstream*fout); //Bellman - Ford
bool FLOYD(Graph* graph, char option, ofstream* fout);   //FLoyd
bool KWANGWOON(Graph* graph, int vertex, ofstream *fout);


#endif
