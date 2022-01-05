#include<iostream>
#include <vector>
using namespace std;

// Не использовалось в реализации алгоритма Крускала, но требуется по заданию:
// хранение графов (списки смежности, матрицы смежности, инцидентности);
// обход графов (в глубину и в ширину).

vector<vector<int>> nodes;

// обход графа в ширину 
void dfs(int v) 
{
	bool* visited = new bool(nodes.size());
	for (int i = 0; i < nodes.size(); i++) 
	{
		visited[i] = false;
	}
	visited[v] = true;
	for (auto next : nodes[v]) 
	{
		if (!visited[next]) 
		{
			dfs(next);
		}
	}
}

//обход графа в ширину 
void bfs (int v)
{
	bool* visited = new bool(nodes.size());
	vector<int> queue;
	queue.push_back(v);

	while (!queue.empty())
	{
		int node =  queue[0];
		queue.erase(queue.begin());
		if (!visited[node]) 
		{
			for (size_t i = 0; i < nodes[node].size(); i++) 
			{
				int to = nodes[node][i];
				if (visited[to] == 0) 
				{
					visited[to] = true;
					queue.push_back(to);
				}
			}
		}
	}
}

// Матрица смежности
void matrixAdj(vector<pair<int, int>> graf, bool** matrix) 
{
	for (int i = 0; i <  graf.size();i++) 
	{
		matrix[graf[i].first - 1][graf[i].second - 1] = true;
		matrix[graf[i].second - 1][graf[i].first - 1] = true;
	}
}
// Матрица инцидентности 
void matrixIn(vector<pair<int, int>> edge, bool** vertex)
{
	for (int  i; i< edge.size();i++) 
	{
		vertex[i][edge[i].first - 1] = true;
		vertex[i][edge[i].second - 1] = true;
	}
}
//Список смежности
void listCon(vector<pair<int, int>> graf, vector<vector<int>> list, int v)
{
	vector<int> temp;
	for (int i = 0; i < v; i++) { list.push_back(temp); }
	for (int i = 0; i < graf.size();i++) 
	{
		list[graf[i].first - 1].push_back(graf[i].second);
		list[graf[i].second - 1].push_back(graf[i].first);
	}
}