#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>

using namespace std;



bool BFS(Graph* graph, char option, int vertex, ofstream* fout)
{
	//인접한 것이 없을 때 처리 필요
	bool* visited = new bool[graph->getSize() + 1];
	queue<int>que;

	for (int i = 0; i < graph->getSize() + 1; i++)
		visited[i] = false;

	*fout << "======== BFS ========" << endl;

	if (option == 'Y' || option == 'N')
	{
		if (option == 'Y')
		{
			*fout << "Directed Graph BFS result" << endl;
		}
		else
		{
			*fout << "Undirected Graph BFS result" << endl;
		}
	}
	else return false;

	int flag = 0;
	int current = 0; map<int, int> relation;

	que.push(vertex);
	visited[vertex] = true;

	*fout << "startvertex: " << vertex << endl;
	*fout << vertex << " -> "; 

	while (!que.empty())
	{
		current = que.front();
		que.pop();
		graph->getAdjacentEdges(current, &relation, option);
		for (auto it = relation.begin(); it != relation.end(); it++)
		{
			int neighbor = it->first;
			if (!visited[neighbor])
			{
				que.push(neighbor);
				visited[neighbor] = true;
				*fout << neighbor;
				*fout << " -> ";
			}
		}
		relation.clear();
	}
	*fout << endl << "=====================" << endl;
	delete[] visited;

	return true;
}

bool DFS(Graph* graph, char option, int vertex, ofstream* fout)
{
	//인접한 것이 없을 때 처리 필요
	bool* visited = new bool[graph->getSize()+1];
	stack<int>stk;

	for (int i = 0; i < graph->getSize()+1; i++)
		visited[i] = false;

	*fout << "======== DFS ========" << endl;

	if (option == 'Y' || option == 'N')
	{
		if (option == 'Y')
		{
			*fout << "Directed Graph DFS result" << endl;
		}
		else
		{
			*fout << "Undirected Graph DFS result" << endl;
		}
	}
	else return false;


	int flag = 0;
	int current = 0; map<int, int> relation;

	stk.push(vertex);
	visited[vertex] = true;

	*fout << "startvertex: " << vertex << endl;
	*fout << vertex; flag++;
	if (flag != graph->getSize()) *fout << " -> ";

	while (!stk.empty())
	{
		current = stk.top();
		stk.pop();
		graph->getAdjacentEdges(current, &relation, option);
		for (auto it = relation.begin(); it != relation.end(); it++)
		{
			int neighbor = it->first;
			if (!visited[neighbor])
			{
				stk.push(current);
				stk.push(neighbor);
				visited[neighbor] = true;
				*fout << neighbor; flag++;
				if (flag != graph->getSize()) *fout << " -> ";
				break;
			}
		}
		relation.clear();
	}
	*fout << endl << "=====================" << endl;
	delete[] visited;

	return true;
}

void InsertionSort(vector<pair<int, pair<int, int>>>& E, int low, int high)
{
	for (int j = low+1; j <= high; j++)
	{
		int i = j - 1;
		pair<int, pair<int, int>> key = E[j];
		while (i > -1)
		{
			if (E[i].first <= key.first) break;
			E[i + 1] = E[i];
			i--;
		}
		E[i + 1] = key;
	}
}

void QuickSort(vector<pair<int, pair<int, int>>>& E, int low, int high)
{
	if (low < high)
	{
		if (high - low + 1 <= 6)
			InsertionSort(E, low, high);
		else
		{
			int i = low, j = high + 1, pivot = E[low].first;
			do {
				do i++; while (E[i].first < pivot);
				do j--; while (E[j].first > pivot);
				if (i < j) swap(E[i], E[j]);
			} while (i < j);
			swap(E[low], E[j]);
			QuickSort(E, low, j - 1);
			QuickSort(E, j + 1, high);
		}
	}
}
int Find(int* prev, int tofind)
{
	if (prev[tofind] == tofind) return tofind;
	else return Find(prev,prev[tofind]);
}

void Union(int* prev, int smallone, int bigone)
{
	if (smallone < bigone)prev[bigone] = smallone;
	else prev[smallone] = bigone;
}

bool isUnion(int* prev, int newone, int oldone)
{
	if (Find(prev, newone) == Find(prev,oldone)) return true;
	else return false;
}

bool Kruskal(Graph* graph, ofstream* fout)
{
	//pair <int WEIGHT, pair<START, END>>
	vector<pair<int, pair<int, int>>> E;
	map<int, int> relation;
	for (int i = 1; i <= graph->getSize(); i++)
	{
		graph->getAdjacentEdgesDirect(i, &relation);
		for (auto itr = relation.begin(); itr != relation.end(); itr++)
		{
			E.push_back(make_pair(itr->second, make_pair(i, itr->first)));
		}
		relation.clear();
	}
	QuickSort(E, 0, E.size()-1);
	*fout << E.begin()->first << E.rbegin()->first << " " << E.size();
	int* prev = new int[graph->getSize() + 1];
	for (int i = 0; i <= graph->getSize(); i++)
		prev[i] = -1;

	map<int, int>* T = new map<int, int>[graph->getSize() + 1];

	int tt = 0; int ee = 0;
	pair<int, pair<int, int>> edge;

	int v, w, cost,totalcost=0;
	while (tt < graph->getSize() - 1 && ee < E.size() + 1)
	{
		edge = E[ee]; ee++;
		v = edge.second.first;
		w = edge.second.second;
		cost = edge.first;
		if (!isUnion(prev, v, w))
		{
			Union(prev, Find(prev, v), Find(prev, w));
			T[v].insert(map<int, int>::value_type(w, cost));
			tt++;
		}
	}
	if (tt < graph->getSize() - 1||T->empty())
	{
		delete[] prev;
		delete[] T;
		return false;
	}
	for (int i = 1; i <= graph->getSize(); i++)
	{
		for (auto itr = T[i].begin(); itr != T[i].end(); itr++)
		{
			totalcost += itr->second;
		}
	}
	*fout << "======== Kruskal ========" << endl;
	for (int i = 1; i <= graph->getSize(); i++)
	{
		if (!T[i].empty())
		{
			*fout << "[" << i << "]      ";
			for (auto itr = T[i].begin(); itr != T[i].end(); itr++)
			{
				*fout << itr->first << "(" << itr->second << ")";
			}
			cout << endl;
		}
	}
	*fout << "cost: " << totalcost << endl;
	*fout << "=====================" << endl;
	delete[] prev;
	delete[] T;
	return true;
}

bool Dijkstra(Graph* graph, char option, int vertex, ofstream *fout)
{
	//음수 예외처리!!
	//인접한 것이 없을 때 처리 필요

	int* dist = new int[graph->getSize() + 1];
	bool* shortest = new bool[graph->getSize() + 1];
	int* prev = new int[graph->getSize() + 1];
	for (int i = 1; i <= graph->getSize(); i++)
	{
		shortest[i] = false;
		dist[i] = graph->getLength(vertex, i, option);
		prev[i] = -1;
	}
	shortest[vertex] = true;
	dist[vertex] = 0;

	

	*fout << "======== Dijkstra ========" << endl;
	if (option == 'Y' || option == 'N')
	{
		if (option == 'Y')
		{
			*fout << "Directed Graph Dijkstra result" << endl;
		}
		else
		{
			*fout << "Undirected Graph Dijkstra result" << endl;
		}
	}
	else return false;

	map<int, int> relation;
	graph->getAdjacentEdges(vertex, &relation, option);
	for (auto itr = relation.begin(); itr != relation.end(); itr++)
	{
		prev[itr->first] = vertex;
	}
	relation.clear();

	*fout << "startvertex: " << vertex << endl;

	int u; int uweight=INT32_MAX;
	for (int i = 0; i < graph->getSize() - 1; i++)
	{
		uweight=INT32_MAX;
		for (int z = 1; z <= graph->getSize(); z++)
		{
			if (uweight > dist[z] && !shortest[z])
			{
				u = z; uweight = dist[z];
			}
		}
		shortest[u] = true;

		for (int w = 1; w <= graph->getSize(); w++)
		{
			if (!shortest[w])
			{
				if (dist[u] + graph->getLength(u, w, option) < dist[w])
				{
					dist[w] = dist[u] + graph->getLength(u, w, option);
					prev[w] = u;
				}
			}
		}
	}
	int nprev = 0;
	for (int i = 1; i <= graph->getSize(); i++)
	{
		if (i != vertex)
		{
			*fout << "[" << i << "] ";
			stack<int> toPrint;
			nprev = prev[i];
			while (nprev != -1)
			{
				toPrint.push(nprev);
				nprev = prev[nprev];
			}
			while (!toPrint.empty())
			{
				nprev = toPrint.top();
				toPrint.pop();
				*fout << nprev << " -> ";
			}
			if(prev[i]==-1) *fout << i << " (X)" << endl;
			else *fout <<i<< " (" << dist[i] << ")" << endl;
		}
	}

	*fout << "=====================" << endl;
	delete[] dist;
	delete[] shortest;
	delete[] prev;
	return true;
}

bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex, ofstream*fout) 
{
	//error code 출력
	int* dist = new int[graph->getSize() + 1];
	int* prev = new int[graph->getSize() + 1];
	for (int i = 0; i <= graph->getSize(); i++)
	{
		dist[i] = graph->getLength(s_vertex, i, option);
		prev[i] = -1;
	}
	map<int, int> relation;
	graph->getAdjacentEdges(s_vertex, &relation, option);
	for (auto itr = relation.begin(); itr != relation.end(); itr++)
	{
		prev[itr->first] = s_vertex;
	}
	relation.clear();


	for (int k = 2; k <= graph->getSize() - 1; k++)
	{
		for (int v = 1; v <= graph->getSize(); v++)
		{
			if (option == 'Y') graph->getIncomingEdges(v, &relation);
			else graph->getAdjacentEdgesUnDirect(v, &relation);
			if (!relation.empty() && v != s_vertex)
			{
				for (int w = 1; w <= graph->getSize(); w++)
				{
					if (dist[v] > dist[w] + graph->getLength(w, v, option))
					{
						dist[v] = dist[w] + graph->getLength(w, v, option);
						prev[v] = w;
					}
				}
			}
			relation.clear();
		}
	}
	for (int v = 1; v <= graph->getSize(); v++)
	{
		if (option == 'Y') graph->getIncomingEdges(v, &relation);
		else graph->getAdjacentEdgesUnDirect(v, &relation);
		if (!relation.empty() && v != s_vertex)
		{
			for (int w = 1; w <= graph->getSize(); w++)
			{
				if (dist[v] > dist[w] + graph->getLength(w, v, option))
				{
					delete[] dist;
					delete[] prev;
					return false;
				}
			}
		}
		relation.clear();
	}
	*fout << "======== Bellman-Ford ========" << endl;
	if (option == 'Y' || option == 'N')
	{
		if (option == 'Y')
		{
			*fout << "Directed Graph Bellman-Ford result" << endl;
		}
		else
		{
			*fout << "Undirected Graph Bellman-Ford result" << endl;
		}
	}
	int nprev = 0; bool exist = false;
	stack<int> toPrint;
	nprev = prev[e_vertex];
	while (nprev!=-1)
	{
		toPrint.push(nprev);
		nprev = prev[nprev];
	}
	while (!toPrint.empty())
	{
		nprev = toPrint.top();
		toPrint.pop();
		*fout << nprev << " -> ";
		exist = true;
	}
	if (!exist) *fout << "X" << endl;
	else if (prev[e_vertex] == -1) *fout << e_vertex << " (X)" << endl;
	else *fout << e_vertex << " (" << dist[e_vertex] << ")" << endl;

	*fout << "=====================" << endl;
	delete[] dist;
	delete[] prev;
	return true;
}

bool FLOYD(Graph* graph, char option, ofstream* fout)
{
	int** A = new int*[graph->getSize() + 1];
	int i, j, k;
	for (i = 1; i <= graph->getSize(); i++)
	{
		A[i] = new int[graph->getSize() +1];
	}

	for (i = 1; i <= graph->getSize(); i++)
	{
		for (j = 1; j <= graph->getSize(); j++)
		{
			A[i][j] = graph->getLength(i, j, option);
		}
	}

	for (k = 1; k <= graph->getSize(); k++)
	{
		for (i = 1; i <= graph->getSize(); i++)
		{
			for (j = 1; j <= graph->getSize(); j++)
			{
				if (A[i][k] == 800000000 || A[k][j] == 800000000) continue;
				else if (A[i][j] > A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];
				}
			}
		}
	}
	for (i = 1; i <= graph->getSize(); i++)
	{
		if (A[i][i] < 0)
		{
			for (k = 1; k <= graph->getSize(); k++)
			{
				delete[] A[k];
			}
			delete[] A;
			return false;
		}
	}

	*fout << "======== FLOYD ========" << endl;
	if (option == 'Y' || option == 'N')
	{
		if (option == 'Y')
		{
			*fout << "Directed Graph FLOYD result" << endl;
		}
		else
		{
			*fout << "Undirected Graph FLOYD result" << endl;
		}
	}
	*fout << "  " << setw(4);
	for (int j = 1; j <= graph->getSize(); j++)
	{
		*fout << setw(2) << "[" << j << "]";
	}*fout << endl;
	for (int i = 1; i <= graph->getSize(); i++)
	{
		*fout << "[" << i << "] ";
		for (int j = 1; j <= graph->getSize(); j++)
		{
			if(A[i][j]== 800000000) *fout << "X" << setw(4);
			else *fout << A[i][j] << setw(4);
		}
		*fout << endl << setw(0);
	}
	*fout << "=====================" << endl;

	for (i = 1; i <= graph->getSize(); i++)
	{
		delete[] A[i];
	}
	delete[] A;
	return true;
}

bool KWANGWOON(Graph* graph, int vertex) {
	return true;
}