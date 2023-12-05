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
	bool* visited = new bool[graph->getSize() + 1];
	queue<int>que;

	for (int i = 0; i < graph->getSize() + 1; i++)
		visited[i] = false;

	*fout << "======== BFS ========" << endl;

	bool direct = false;
	if (option == 'Y' || option == 'N')
	{
		if (option == 'Y')
		{
			direct = true;
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
		graph->getAdjacentEdges(current, &relation, direct);
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
	bool* visited = new bool[graph->getSize()+1];
	stack<int>stk;

	for (int i = 0; i < graph->getSize()+1; i++)
		visited[i] = false;

	*fout << "======== DFS ========" << endl;

	bool direct = false;
	if (option == 'Y' || option == 'N')
	{
		if (option == 'Y')
		{
			direct = true;
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
		graph->getAdjacentEdges(current, &relation, direct);
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


bool Kruskal(Graph* graph)
{
	return true;
}

bool Dijkstra(Graph* graph, char option, int vertex, ofstream *fout)
{
	//음수 예외처리!!


	bool direct = false;
	
	int* dist = new int[graph->getSize() + 1];
	bool* shortest = new bool[graph->getSize() + 1];
	int* prev = new int[graph->getSize() + 1];
	for (int i = 1; i <= graph->getSize(); i++)
	{
		shortest[i] = false;
		dist[i] = graph->getLength(vertex, i, direct);
		prev[i] = -1;
	}
	shortest[vertex] = true;
	dist[vertex] = 0;

	

	*fout << "======== Dijkstra ========" << endl;
	if (option == 'Y' || option == 'N')
	{
		if (option == 'Y')
		{
			direct = true;
			*fout << "Directed Graph Dijkstra result" << endl;
		}
		else
		{
			*fout << "Undirected Graph Dijkstra result" << endl;
		}
	}
	else return false;

	map<int, int> relation;
	graph->getAdjacentEdges(vertex, &relation, direct);
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
				if (dist[u] + graph->getLength(u, w, direct) < dist[w])
				{
					dist[w] = dist[u] + graph->getLength(u, w, direct);
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

bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex) 
{
	return true;
}

bool FLOYD(Graph* graph, char option)
{
	return true;
}

bool KWANGWOON(Graph* graph, int vertex) {
	return true;
}