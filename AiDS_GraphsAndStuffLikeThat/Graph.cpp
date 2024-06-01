#include "Graph.h"
#include <iostream>

void Graph::Dfs(long long v)
{
	visited[v] = true;
	for (long long i = 0; i < verticesDegrees[v]; i++)
	{
		long long x = adjacencyList[v][i] - 1;
		if (!visited[x])
		{
			Dfs(x);
		}
	}
}

bool Graph::DfsCheck(long long v, long long colour)
{
	verticesColours[v] = (colour == 0 ? 1 : 0);
	for (long long i = 0; i < verticesDegrees[v]; i++)
	{
		long long x = adjacencyList[v][i] - 1;
		if (verticesColours[x] == -1)
		{
			if (!DfsCheck(x, verticesColours[v])) return false;
		}
		else if (verticesColours[x] == verticesColours[v])
		{
			return false;
		}
	}
	return true;
}

void Graph::Merge(int* arr, int left, int mid, int right, int* arr2)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int* L = new int[n1];
	int* R = new int[n2];
	int* L2 = nullptr;
	if (arr2 != nullptr) L2 = new int[n1];
	int* R2 = nullptr;
	if (arr2 != nullptr) R2 = new int[n2];

	for (int i = 0; i < n1; i++)
	{
		L[i] = arr[left + i];
		if (arr2 != nullptr) L2[i] = arr2[left + i];
	}
	for (int j = 0; j < n2; j++)
	{
		R[j] = arr[mid + 1 + j];
		if (arr2 != nullptr) R2[j] = arr2[mid + 1 + j];
	}

	int i = 0;
	int j = 0;
	int k = left;

	while (i < n1 && j < n2)
	{
		if (L[i] >= R[j])
		{
			arr[k] = L[i];
			if (arr2 != nullptr) arr2[k] = L2[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			if (arr2 != nullptr) arr2[k] = R2[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		if (arr2 != nullptr) arr2[k] = L2[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		if (arr2 != nullptr) arr2[k] = R2[j];
		j++;
		k++;
	}

	delete[] L;
	delete[] R;
	if (arr2 != nullptr) delete[] L2;
	if (arr2 != nullptr) delete[] R2;
}

void Graph::MergeSort(int* arr, int left, int right, int* arr2)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		MergeSort(arr, left, mid, arr2);
		MergeSort(arr, mid + 1, right, arr2);
		Merge(arr, left, mid, right, arr2);
	}
}

Graph::Graph()
{
	std::cin >> graphOrder;
	int tempGraphOrder = (int)graphOrder;
	adjacencyList = new int* [tempGraphOrder];
	verticesDegrees = new int[tempGraphOrder];
	visited = new bool[tempGraphOrder];
	verticesColours = new int[tempGraphOrder];
	for (int i = 0; i < graphOrder; i++)
	{
		int vertexDegree = 0;
		std::cin >> vertexDegree;
		adjacencyList[i] = new int[vertexDegree];
		verticesDegrees[i] = vertexDegree;
		visited[i] = false;
		verticesColours[i] = -1;
		for (int k = 0; k < vertexDegree; k++)
		{
			std::cin >> adjacencyList[i][k];
		}
	}
}

long long Graph::GetGraphOrder() const
{
	return graphOrder;
}

int* Graph::DegreeSequence()
{
	int tempGraphOrder = (int)graphOrder;
	int* degreeSequence = new int[tempGraphOrder];
	for (int i = 0; i < graphOrder; i++)
	{
		degreeSequence[i] = verticesDegrees[i];
	}
	MergeSort(degreeSequence, 0, tempGraphOrder - 1);
	return degreeSequence;
}

int Graph::NumberOfComponents()
{
	int componentCount = 0;
	for (int i = 0; i < graphOrder; i++) {
		if (!visited[i]) {
			Dfs(i);
			componentCount++;
		}
	}
	return componentCount;
}

bool Graph::IsBipartite()
{
	for (int i = 0; i < graphOrder; ++i)
	{
		if (verticesColours[i] == -1)
		{
			if (!DfsCheck(i, 0))
			{
				return false;
			}
		}
	}
	return true;
}

//int* Graph::EccentricityOfVertices()
//{
	//return nullptr;
//}

//bool Graph::IsPlanar()
//{
	//return false;
//}

int* Graph::VerticesColoursGreedy()
{
	int tempGraphOrder = (int)graphOrder;
	int* colours = new int[tempGraphOrder];
	bool* available = new bool[tempGraphOrder + 1];
	for (int i = 0; i < graphOrder; i++)
	{
		colours[i] = 0;
		available[i] = true;
	}
	available[tempGraphOrder] = true;
	colours[0] = 1;

	for (int u = 1; u < graphOrder; u++)
	{
		for (int i = 0; i < verticesDegrees[u]; i++)
		{
			if (colours[adjacencyList[u][i] - 1] != 0)
			{
				available[colours[adjacencyList[u][i] - 1]] = false;
			}
		}

		int colour;
		for (colour = 1; colour <= graphOrder; colour++)
		{
			if (available[colour])
			{
				break;
			}
		}

		colours[u] = colour;

		for (int i = 0; i < verticesDegrees[u]; i++)
		{
			if (colours[adjacencyList[u][i] - 1] != 0)
			{
				available[colours[adjacencyList[u][i] - 1]] = true;
			}
		}
	}
	delete[] available;
	return colours;
}

int* Graph::VerticesColoursLF()
{
	int tempGraphOrder = (int)graphOrder;
	int* degrees = new int[tempGraphOrder];
	int* indices = new int[tempGraphOrder];
	for (int u = 0; u < graphOrder; u++)
	{
		degrees[u] = verticesDegrees[u];
		indices[u] = u;
	}

	MergeSort(degrees, 0, tempGraphOrder - 1, indices);
	delete[] degrees;

	int* colours = new int[tempGraphOrder];
	bool* available = new bool[tempGraphOrder + 1];
	for (int i = 0; i < graphOrder; i++)
	{
		colours[i] = 0;
		available[i] = true;
	}
	available[tempGraphOrder] = true;

	for (int i = 0; i < graphOrder; i++)
	{
		int u = indices[i];

		for (int k = 0; k < verticesDegrees[u]; k++)
		{
			if (colours[adjacencyList[u][k] - 1] != 0)
			{
				available[colours[adjacencyList[u][k] - 1]] = false;
			}
		}

		int colour;
		for (colour = 1; colour <= graphOrder; colour++)
		{
			if (available[colour])
			{
				break;
			}
		}

		colours[u] = colour;

		for (int k = 0; k < verticesDegrees[u]; k++)
		{
			if (colours[adjacencyList[u][k] - 1] != 0)
			{
				available[colours[adjacencyList[u][k] - 1]] = true;
			}
		}
	}
	delete[] indices;
	delete[] available;
	return colours;
}

//int* Graph::VerticesColoursSLF()
//{
	//return nullptr;
//}

long long Graph::DifferentC4SubgraphsNumber() const
{
	long long count = 0;
	for (long long u = 0; u < graphOrder; ++u) 
	{
		for (long long k = 0; k < verticesDegrees[u]; ++k) 
		{
			long long v = adjacencyList[u][k] - 1;
			if (v <= u) continue;
			
			for (long long i = 0; i < verticesDegrees[u]; ++i) 
			{
				long long w = adjacencyList[u][i] - 1;
				if (w == v) continue;

				for (long long j = 0; j < verticesDegrees[v]; ++j) 
				{
					long long x = adjacencyList[v][j] - 1;
					if (x == u || x == w) continue;

					for (long long q = 0; q < verticesDegrees[w]; ++q) 
					{
						if (adjacencyList[w][q] - 1 == x) 
						{
							count++;
							break;
						}
					}
				}
			}
		}
	}
	return count / 4;
}

long long Graph::GraphComplementsEdgesNumber() const
{
	long long completeGraphEdgesNumber = graphOrder * (graphOrder - 1) / 2;
	long long thisGraphEdgesNumber = 0;
	for (int i = 0; i < graphOrder; i++)
	{
		thisGraphEdgesNumber += verticesDegrees[i];
	}
	thisGraphEdgesNumber /= 2;
	return completeGraphEdgesNumber - thisGraphEdgesNumber;
}

Graph::~Graph()
{
	for (int i = 0; i < graphOrder; i++)
	{
		delete[] adjacencyList[i];
	}
	delete[] adjacencyList;
	delete[] verticesDegrees;
	delete[] visited;
	delete[] verticesColours;
}