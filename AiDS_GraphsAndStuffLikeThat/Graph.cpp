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

void Graph::Merge(int arr[], int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// Create temporary arrays
	int* L = new int[n1];
	int* R = new int[n2];

	// Copy data to temporary arrays L[] and R[]
	for (int i = 0; i < n1; i++) 
	{
		L[i] = arr[left + i];
	}
	for (int j = 0; j < n2; j++)
	{
		R[j] = arr[mid + 1 + j];
	}

	// Merge the temporary arrays back into arr[left..right]
	int i = 0; // Initial index of first subarray
	int j = 0; // Initial index of second subarray
	int k = left; // Initial index of merged subarray

	while (i < n1 && j < n2) 
	{
		if (L[i] >= R[j]) 
		{
			arr[k] = L[i];
			i++;
		}
		else 
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[], if there are any
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[], if there are any
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}

	// Free the allocated memory
	delete[] L;
	delete[] R;
}

void Graph::MergeSort(int arr[], int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;

		// Sort first and second halves
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);

		// Merge the sorted halves
		Merge(arr, left, mid, right);
	}
}

Graph::Graph()
{
	std::cin >> graphOrder;
	int tempGraphOrder = (int)graphOrder;
	adjacencyList = new int*[tempGraphOrder];
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
			int temp = 0;
			std::cin >> temp;
			adjacencyList[i][k] = temp;
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

int* Graph::EccentricityOfVertices()
{
	return nullptr;
}

bool Graph::IsPlanar()
{
	return false;
}

int* Graph::VerticesColoursGreedy()
{
	return nullptr;
}

int* Graph::VerticesColoursLF()
{
	return nullptr;
}

int* Graph::VerticesColoursSLF()
{
	return nullptr;
}

int Graph::DifferentC4SubgraphsNumber()
{
	return 0;
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
