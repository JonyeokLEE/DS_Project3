#include "Manager.h"
#include "GraphMethod.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

Manager::Manager()	
{
	graph = nullptr;	
	fout.open("log.txt", ios::app);
	load = 0;	//Anything is not loaded
	isList = false; //for kw graph
}

Manager::~Manager()
{
	if(load)	//if graph is loaded, delete graph
		delete graph;	
	if(fout.is_open())	//if fout is opened, close file
		fout.close();	//close log.txt File
}

void Manager::run(const char* command_txt){
	ifstream fin;	//Command File Input File Stream
	fin.open(command_txt, ios_base::in);//File open with read mode
	
	if(!fin) { //If command File cannot be read, Print error
		fout<<"command file open error"<<endl;
		return;	//Return
	}
	
	string cmd;
	bool success; int parameter = 0;
	while (!fin.eof())
	{
		getline(fin, cmd);
		parameter = 0;
		if (cmd.substr(0, 4) == "LOAD") //LOAD
		{
			vector<string> tosplit;
			stringstream ss(cmd);
			string temp;

			while (getline(ss, temp, ' '))
			{
				tosplit.push_back(temp);
			}

			if (tosplit.size() != 2)
			{
				printErrorCode(100);
				continue;
			}
			string filename = cmd.substr(5);
			success = LOAD(filename.c_str());
			if (success)
			{
				fout << "======== LOAD ========" << endl;
				fout << "Success" << endl;
				fout << "=====================" << endl << endl;
			}
			if (!success) printErrorCode(100);
		}
		else if (cmd.substr(0, 5) == "PRINT") //PRINT
		{
			vector<string> tosplit;
			stringstream ss(cmd);
			string temp;

			while (getline(ss, temp, ' '))
			{
				tosplit.push_back(temp);
			}

			if (load==0||tosplit.size() != 1)
			{
				printErrorCode(200);
				continue;
			}
			success = PRINT();
			if (!success) printErrorCode(200);
		}
		else if (cmd.substr(0, 3) == "DFS") //DFS
		{
			vector<string> tosplit;
			stringstream ss(cmd);
			string temp;

			while (getline(ss, temp, ' '))
			{
				tosplit.push_back(temp);
			}

			if (load == 0 || tosplit.size() != 3)
			{
				printErrorCode(400);
				continue;
			}
			char option = cmd.substr(4, 1).c_str()[0];
			int vertex = stoi(cmd.substr(6));
			success = mDFS(option,vertex);
			if (!success) printErrorCode(400);
		}
		else if (cmd.substr(0, 3) == "BFS") //BFS
		{
			vector<string> tosplit;
			stringstream ss(cmd);
			string temp;

			while (getline(ss, temp, ' '))
			{
				tosplit.push_back(temp);
			}

			if (load == 0 || tosplit.size() != 3)
			{
				printErrorCode(300);
				continue;
			}
			char option = cmd.substr(4, 1).c_str()[0];
			int vertex = stoi(cmd.substr(6));
			success = mBFS(option, vertex);
			if (!success) printErrorCode(300);
		}
		else if (cmd.substr(0, 8) == "DIJKSTRA") //DJIKSTRA
		{
			vector<string> tosplit;
			stringstream ss(cmd);
			string temp;

			while (getline(ss, temp, ' '))
			{
				tosplit.push_back(temp);
			}

			if (load == 0 || tosplit.size() != 3)
			{
				printErrorCode(700);
				continue;
			}
			char option = cmd.substr(9, 1).c_str()[0];
			int vertex = stoi(cmd.substr(11));
			success = mDIJKSTRA(option, vertex);
			if (!success) printErrorCode(700);
		}
		else if (cmd.substr(0, 7) == "KRUSKAL") //KRUSKAL
		{
			vector<string> tosplit;
			stringstream ss(cmd);
			string temp;

			while (getline(ss, temp, ' '))
			{
				tosplit.push_back(temp);
			}

			if (load == 0 || tosplit.size() != 1)
			{
				printErrorCode(600);
				continue;
			}
			success = mKRUSKAL();
			if (!success) printErrorCode(600);
		}
		else if (cmd.substr(0, 11) == "BELLMANFORD") //BELLMANFORD
		{
			vector<string> tosplit;
			stringstream ss(cmd);
			string temp;

			while (getline(ss, temp, ' '))
			{
				tosplit.push_back(temp);
			}

			if (load == 0 || tosplit.size() != 4)
			{
				printErrorCode(800);
				continue;
			}
			char option = cmd.substr(12,1).c_str()[0];
			int s_vertex = stoi(cmd.substr(14));
			int e_vertex = stoi(cmd.substr(16));
			success = mBELLMANFORD(option, s_vertex, e_vertex);
			if (!success) printErrorCode(800);
		}
		else if (cmd.substr(0, 5) == "FLOYD") //FLOYD
		{
			vector<string> tosplit;
			stringstream ss(cmd);
			string temp;

			while (getline(ss, temp, ' '))
			{
				tosplit.push_back(temp);
			}

			if (load == 0 || tosplit.size() != 2)
			{
				printErrorCode(900);
				continue;
			}
			char option = cmd.substr(6, 1).c_str()[0];
			success = mFLOYD(option);
			if (!success) printErrorCode(900);
		}
		else if (cmd.substr(0, 9) == "KWANGWOON") //KWANGWOON
		{
			vector<string> tosplit;
			stringstream ss(cmd);
			string temp;

			while (getline(ss, temp, ' '))
			{
				tosplit.push_back(temp);
			}

			if (load == 0 || tosplit.size() != 1)
			{
				printErrorCode(500);
				continue;
			}
			if (!isList)
			{
				printErrorCode(500);
				continue;
			}
			success = mKwoonWoon(1);
			if (!success) printErrorCode(500);
		}
		else if (cmd.substr(0, 4) == "EXIT") //EXIT
		{
			break;
		}
		else
		{
			if (!success) printErrorCode(1000);
		}
	}

	fin.close();
	return;
}

bool Manager::LOAD(const char* filename) //LOAD
{
	ifstream readfile;
	readfile.open(filename, ios_base::in);//File open with read mode

	if (!readfile) { //If command File cannot be read, Print error
		return false;
	}
	if (load == 1) delete graph; //there were graph data before, delete former data
	if (strcmp(filename,"graph_L.txt")==0) //LIST
	{
		isList = true;
		load = 1;
		string line;
		getline(readfile, line);
		getline(readfile, line);
		graph = new ListGraph(0, stoi(line));
		int from = 0; int to = 0; int weight = 0;
		while (!readfile.eof())
		{
			getline(readfile, line);
			vector<string> tosplit;
			stringstream ss(line);
			string temp;

			while (getline(ss, temp, ' '))
			{
				tosplit.push_back(temp);
			}

			if (tosplit.size() == 1)
			{
				from = stoi(tosplit.at(0));
			}
			else if (tosplit.size() == 2)
			{
				to = stoi(tosplit.at(0)); 
				weight = stoi(tosplit.at(1));
				graph->insertEdge(from, to, weight); //split and insert
			}
			else
				return false;
		}
		return true;
	}
	else if (strcmp(filename, "graph_M.txt") == 0) //MATRIX
	{
		isList = false;
		load = 1;
		string line;
		getline(readfile, line);
		getline(readfile, line);
		int size = stoi(line);
		graph = new MatrixGraph(1, size);
		int from = 0; int to = 0; int weight = 0;
		while (!readfile.eof())
		{
			from++;
			getline(readfile, line);
			vector<string> tosplit;
			stringstream ss(line);
			string temp;
			
			while (getline(ss, temp, ' '))
			{
				tosplit.push_back(temp);
			}

			if (tosplit.size() == size)
			{
				for (int i = 1; i <= size; i++)
				{
					graph->insertEdge(from, i, stoi(tosplit.at(i - 1))); //split and insert
				}
			}
			else
				return false;
		}
		return true;
	}
	else
	{
		load = 0;
		return false;
	}
}

bool Manager::PRINT() //PRINT
{
	if (!fout||!fout.is_open()) return false;
	return graph->printGraph(&fout);
}

bool Manager::mBFS(char option, int vertex)	//BFS
{
	return BFS(graph, option, vertex, &fout);
}

bool Manager::mDFS(char option, int vertex)	//DFS
{
	return DFS(graph, option, vertex, &fout);
}

bool Manager::mDIJKSTRA(char option, int vertex) //DIJKSTRA
{
	return Dijkstra(graph, option, vertex, &fout);
}

bool Manager::mKRUSKAL() //KRUSKAL
{
	return Kruskal(graph, &fout);
}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex) //BELLMANFORD
{
	return Bellmanford(graph, option, s_vertex, e_vertex, &fout);
}

bool Manager::mFLOYD(char option) //FLOYD
{
	return FLOYD(graph, option, &fout);
}

bool Manager::mKwoonWoon(int vertex) //KWANGWOON
{
	return KWANGWOON(graph, 1, &fout);
}

void Manager::printErrorCode(int n) //to print error code
{
	fout<<"========ERROR======="<<endl;
	fout<<n<<endl;
	fout<<"===================="<<endl << endl;
}


