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

bool Dijkstra(Graph* graph, char option, int vertex)
{
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