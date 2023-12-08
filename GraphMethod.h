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

int init(int node, int start, int end, vector<int>& _arr, vector<int>& _seg);
void update(int node, int start, int end, int target, int diff_value, vector<int>& _arr, vector<int>& _seg);
int sum(int node, int start, int end, int left, int right, vector<int>& _arr, vector<int>& _seg);
bool KWANGWOON(Graph* graph, int vertex, ofstream *fout);


#endif
