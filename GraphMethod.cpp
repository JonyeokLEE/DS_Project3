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



bool BFS(Graph* graph, char option, int vertex, ofstream* fout) //BFS
{
	bool* visited = new bool[graph->getSize() + 1];
	queue<int>que; //for FIFO way

	for (int i = 0; i < graph->getSize() + 1; i++)
		visited[i] = false; //did i visited here?

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

	bool flag = false; bool first = false;
	int current = 0; map<int, int> relation; //to get adjacency nodes

	que.push(vertex);
	visited[vertex] = true;

	*fout << "startvertex: " << vertex << endl; 
	*fout << vertex;
	while (!que.empty()) //untill queue is not empty
	{
		current = que.front();
		que.pop();
		graph->getAdjacentEdges(current, &relation, option);
		for (auto it = relation.begin(); it != relation.end(); it++)
		{
			int neighbor = it->first;
			if (!visited[neighbor])
			{
				if (!first)*fout << " -> ";
				que.push(neighbor);
				visited[neighbor] = true;
				if (flag)*fout << " -> ";
				*fout << neighbor;
				flag = true;
				first = true; //for print form
			}
		}
		relation.clear(); //clear map
	}
	*fout << endl << "=====================" << endl << endl;
	delete[] visited;

	return true;
}

bool DFS(Graph* graph, char option, int vertex, ofstream* fout) //DFS
{
	bool* visited = new bool[graph->getSize()+1];
	stack<int>stk; //for LIFO

	for (int i = 0; i < graph->getSize()+1; i++)
		visited[i] = false; //did i visited here?

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


	bool flag = false; bool first = false;
	int current = 0; map<int, int> relation; //to get adjacency nodes

	stk.push(vertex);
	visited[vertex] = true;

	*fout << "startvertex: " << vertex << endl;
	*fout << vertex;

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
				if(!first)*fout << " -> ";
				stk.push(current);
				stk.push(neighbor);
				visited[neighbor] = true;
				if(flag)*fout << " -> ";
				*fout << neighbor;
				flag = true;
				first = true; //for print form
				break;
			}
		}
		relation.clear();
	}
	*fout << endl << "=====================" << endl << endl;
	delete[] visited;

	return true;
}

void InsertionSort(vector<pair<int, pair<int, int>>>& E, int low, int high) //insertion sort
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
		if (high - low + 1 <= 6) //less than 6 -> run insertion sort
			InsertionSort(E, low, high);
		else
		{
			int i = low, j = high + 1, pivot = E[low].first;
			do {
				do i++; while (E[i].first < pivot&&i<high);
				do j--; while (E[j].first > pivot&&j>low+1);
				if (i < j) swap(E[i], E[j]);
			} while (i < j); //to get Pivot
			swap(E[low], E[j]);
			QuickSort(E, low, j - 1);
			QuickSort(E, j + 1, high); //recursive call
		}
	}
}
int Find(int* prev, int tofind) //Find parent
{
	while (prev[tofind]>=0)
	{
		tofind = prev[tofind];
	}
	return tofind;
}

void Union(int* prev, int a, int b) //Union a and b
{
	prev[a] = b;
}

bool isUnion(int* prev, int a, int b) //are they Union?
{
	if (Find(prev, a) == Find(prev,b)) return true;
	else return false;
}

bool Kruskal(Graph* graph, ofstream* fout) //KRUSKAL
{
	vector<pair<int, pair<int, int>>> E; //first is weight, second.first is start, second.second is end
	map<int, int> relation;
	for (int i = 1; i <= graph->getSize(); i++)
	{
		graph->getAdjacentEdgesDirect(i, &relation);
		for (auto itr = relation.begin(); itr != relation.end(); itr++)
		{
			E.push_back(make_pair(itr->second, make_pair(i, itr->first))); //get all edges to E
		}
		relation.clear();
	}
	QuickSort(E, 0, E.size()-1); //nondecreasing order
	int* prev = new int[graph->getSize() + 1];

	for (int i = 0; i <= graph->getSize(); i++)
		prev[i] = -1;

	map<int, int>* T = new map<int, int>[E.size()+1];

	int tt = 1; int ee = 0;
	int v, w, cost,totalcost=0;
	while (tt <= graph->getSize()-1&& ee < E.size())
	{
		cost = E[ee].first;
		v = E[ee].second.first;
		w = E[ee].second.second;
		if (!isUnion(prev,v,w)) //if they do not produce cycle
		{
			Union(prev, Find(prev, v), Find(prev, w));
			T[v].insert(map<int, int>::value_type(w, cost));
			T[w].insert(map<int, int>::value_type(v, cost)); //insert both direction
			tt++;
		}
		ee++;
	} 
	if (tt < graph->getSize() - 1) //fail to get spanning tree
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
	totalcost /= 2; //get totalcost
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
			*fout << endl;
		}
	}
	*fout << "cost: " << totalcost << endl;
	*fout << "=====================" << endl << endl;
	delete[] prev;
	delete[] T;
	return true;
}

bool Dijkstra(Graph* graph, char option, int vertex, ofstream *fout) //DIJKSTRA
{
	map<int, int> relation; //to get adgacency nodes
	for (int i = 1; i <= graph->getSize(); i++)
	{
		graph->getAdjacentEdges(i, &relation, option);
		for (auto itr = relation.begin(); itr != relation.end(); itr++)
		{
			if (itr->second < 0)
			{
				return false;
			}
		}
		relation.clear();
	}
	relation.clear();

	int* dist = new int[graph->getSize() + 1];
	bool* shortest = new bool[graph->getSize() + 1];
	int* prev = new int[graph->getSize() + 1]; //to save prev nodes
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

	graph->getAdjacentEdges(vertex, &relation, option);
	for (auto itr = relation.begin(); itr != relation.end(); itr++)
	{
		prev[itr->first] = vertex;
	}
	relation.clear();

	*fout << "startvertex: " << vertex << endl;

	int u; int uweight=INT32_MAX; //+infinite number
	for (int i = 0; i < graph->getSize() - 1; i++)
	{
		uweight=INT32_MAX;
		for (int z = 1; z <= graph->getSize(); z++)
		{
			if (uweight > dist[z] && !shortest[z])
			{
				u = z; uweight = dist[z]; //update u
			}
		}
		shortest[u] = true; //after getting u, check u is shortest now
		for (int w = 1; w <= graph->getSize(); w++)
		{
			if (!shortest[w])
			{
				if (dist[u] + graph->getLength(u, w, option) < dist[w])
				{
					dist[w] = dist[u] + graph->getLength(u, w, option);
					prev[w] = u;
				}
			} //update dist w
		}
	}
	int nprev = 0;
	for (int i = 1; i <= graph->getSize(); i++)
	{
		if (i != vertex)
		{
			*fout << "[" << i << "] ";
			vector<int> toPrint;
			nprev = prev[i];
			while (nprev != -1)
			{
				toPrint.push_back(nprev);
				nprev = prev[nprev];
			}
			if (toPrint.empty())
			{
				*fout << "X" << endl;
				continue;
			}
			while (!toPrint.empty())
			{
				nprev = toPrint.back();
				toPrint.pop_back();
				*fout << nprev;
				*fout<<" -> ";
			}
			if(prev[i]==-1) *fout << i << " (X)" << endl;
			else *fout <<i<< " (" << dist[i] << ")" << endl;
		}
	}

	*fout << "=====================" << endl << endl;
	delete[] dist;
	delete[] shortest;
	delete[] prev;
	return true;
}

bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex, ofstream*fout) 
{
	int* dist = new int[graph->getSize() + 1];
	int* prev = new int[graph->getSize() + 1];
	for (int i = 0; i <= graph->getSize(); i++)
	{
		dist[i] = graph->getLength(s_vertex, i, option);
		prev[i] = -1;
	}
	map<int, int> relation; //to get adgacency nodes
	graph->getAdjacentEdges(s_vertex, &relation, option);
	for (auto itr = relation.begin(); itr != relation.end(); itr++)
	{
		prev[itr->first] = s_vertex; //update prev
	}
	relation.clear();


	for (int k = 2; k <= graph->getSize() - 1; k++) //k = 2 to n-1
	{
		for (int v = 1; v <= graph->getSize(); v++)
		{
			if (option == 'Y') graph->getIncomingEdges(v, &relation);
			else graph->getAdjacentEdgesUnDirect(v, &relation);
			if (!relation.empty() && v != s_vertex) //if v has at least one incoming edge
			{
				for (int w = 1; w <= graph->getSize(); w++)
				{
					if (dist[v] > dist[w] + graph->getLength(w, v, option))
					{
						dist[v] = dist[w] + graph->getLength(w, v, option);
						prev[v] = w;
					}
				} //update dist[v]
			}
			relation.clear();
		}
	}

	for (int v = 1; v <= graph->getSize(); v++) //if update once again-> it has negative cycle
	{
		if (option == 'Y') graph->getIncomingEdges(v, &relation);
		else graph->getAdjacentEdgesUnDirect(v, &relation);
		if (!relation.empty())
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
	vector<int> toPrint;
	nprev = prev[e_vertex];
	while (nprev!=-1)
	{
		toPrint.push_back(nprev);
		nprev = prev[nprev];
	}
	if (toPrint.empty()) exist = false;
	else if (toPrint.back() != s_vertex) exist = false;
	else
	{
		while (!toPrint.empty())
		{
			nprev = toPrint.back();
			toPrint.pop_back();
			*fout << nprev << " -> ";
			exist = true;
		}
	}
	if (!exist) *fout << "X" << endl;
	else if (prev[e_vertex] == -1) *fout << e_vertex << " (X)" << endl;
	else *fout << e_vertex << endl;
	if(exist)*fout<<"cost: " << dist[e_vertex] << endl;

	*fout << "=====================" << endl << endl;
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

	for (k = 1; k <= graph->getSize(); k++) // k is another edge
	{
		for (i = 1; i <= graph->getSize(); i++) //start
		{
			for (j = 1; j <= graph->getSize(); j++) //end
			{
				if (A[i][k] == 800000000 || A[k][j] == 800000000) continue;
				else if (A[i][j] > A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];
				} //update i to j
			}
		}
	}
	for (i = 1; i <= graph->getSize(); i++) //if it has negative weight for itself, it has negative cycle
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
			if (i == j)*fout << "0" << setw(4);
			else if(A[i][j]== 800000000) *fout << "X" << setw(4);
			else *fout << A[i][j] << setw(4);
		}
		*fout << endl << setw(0);
	}
	*fout << "=====================" << endl << endl;

	for (i = 1; i <= graph->getSize(); i++)
	{
		delete[] A[i];
	}
	delete[] A;
	return true;
}


bool KWANGWOON(Graph* graph, int vertex, ofstream* fout)
{
	map<int, int> relation; //to get adjacency nodes
	vector<int> neighbor; //to save neighbor
	bool* visited = new bool[graph->getSize() + 1];
	for (int i = 0; i <= graph->getSize(); i++)
		visited[i] = false;
	int visitednum = 0;
	int toVisit = 0;
	int toGo = 0;
	int current = vertex;
	queue<int> toPrint; //to print
	toPrint.push(vertex);
	while (visitednum < graph->getSize()-1)
	{
		visited[current] = true;
		visitednum++;
		toVisit = 0; toGo = 0;
		graph->getAdjacentEdgesUnDirect(current, &relation);
		if (relation.empty()) break; //unconnected -> false

		for (auto it = relation.begin(); it != relation.end(); it++)
		{
			if (!visited[it->first])
			{
				toVisit++;
				neighbor.push_back(it->first);
			}
		}
		if (neighbor.empty()) break;
		if (toVisit % 2 == 0) //Even number case
		{
			toVisit = neighbor[0];
			for (int i=0;i<neighbor.size();i++)
			{
				if (!visited[i] && toVisit > neighbor[i]) {
					toVisit = neighbor[i];
				}
			}
		}
		else //Odd number case
		{
			toVisit = neighbor[0];
			for (int i = 0; i < neighbor.size(); i++)
			{
				if (!visited[i] && toVisit < neighbor[i]) {
					toVisit = neighbor[i];
				}
			}
		}
		current = toVisit;
		toPrint.push(current);
		relation.clear();
		neighbor.clear();
	}

	bool exist = false; bool flag = false; bool first = true;
	*fout << "======== KWANGWOON ========" << endl;
	*fout << "startvertex: " << vertex << endl;
	while (!toPrint.empty())
	{
		if (!first)*fout << " -> ";
		current = toPrint.front();
		toPrint.pop();
		if (flag)*fout << " -> ";
		*fout << current;
		flag = true;
		first = true;
		exist = true;
	}
	if (!exist) *fout << "X" << endl;
	*fout << endl<<"=====================" << endl << endl;

	delete[] visited;

	return true;
}