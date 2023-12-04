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
	bool success;
	while (!fin.eof())
	{
		getline(fin, cmd);

		if (cmd.substr(0, 4) == "LOAD")
		{
			string filename = cmd.substr(5);
			success = LOAD(filename.c_str());
			if (success)
			{
				fout << "======== LOAD ========" << endl;
				fout << "Success" << endl;
				fout << "=====================" << endl;

			}
		}
		else if (cmd.substr(0, 5) == "PRINT")
		{
			success = PRINT();
		}
		else if (cmd.substr(0, 3) == "DFS")
		{
			char option = cmd.substr(4, 1).c_str()[0];
			int vertex = stoi(cmd.substr(6));
			success = mDFS(option,vertex);
		}
		else if (cmd.substr(0, 3) == "BFS")
		{
			char option = cmd.substr(4, 1).c_str()[0];
			int vertex = stoi(cmd.substr(6));
			success = mBFS(option, vertex);
		}
		else if (cmd.substr(0, 4) == "EXIT")
		{
			break;
		}
		else
		{

		}
	}

	fin.close();
	return;
}

bool Manager::LOAD(const char* filename)
{
	ifstream readfile;
	readfile.open(filename, ios_base::in);//File open with read mode

	if (!readfile) { //If command File cannot be read, Print error
		return false;
	}

	if (strcmp(filename,"graph_L.txt")==0)
	{
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
				graph->insertEdge(from, to, weight);
			}
			else
				return false;
		}
		return true;
	}
	else if (strcmp(filename, "graph_M.txt") == 0)
	{
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
					graph->insertEdge(from, i, stoi(tosplit.at(i - 1)));
				}
			}
			else
				return false;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool Manager::PRINT()	
{
	if (!fout||!fout.is_open()) return false;
	return graph->printGraph(&fout);
}

bool Manager::mBFS(char option, int vertex)	
{
	return BFS(graph, option, vertex, &fout);
}

bool Manager::mDFS(char option, int vertex)	
{
	return DFS(graph, option, vertex, &fout);
}

bool Manager::mDIJKSTRA(char option, int vertex)	
{
	return true;
}

bool Manager::mKRUSKAL()
{
	return true;
}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex) 
{
	return true;
}

bool Manager::mFLOYD(char option)
{
	return true;
}

bool Manager::mKwoonWoon(int vertex)
{
	return true;
}

void Manager::printErrorCode(int n)
{
	fout<<"========ERROR======="<<endl;
	fout<<n<<endl;
	fout<<"===================="<<endl << endl;
}


