#include "Graph.h"
#include <iostream>

void Graph::Dfs(int v)
{
	visited[v] = true;
	for (int i = 0; i < verticesDegrees[v]; i++) 
	{
		int x = adjacencyList[v][i] - 1;
		if (!visited[x]) 
		{
			Dfs(x);
		}
	}
}

bool Graph::DfsCheck(int v, int colour)
{
	verticesColours[v] = (colour == 0 ? 1 : 0);
	for (int i = 0; i < verticesDegrees[v]; i++)
	{
		int x = adjacencyList[v][i] - 1;
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

Graph::Graph()
{
	std::cin >> graphOrder;
	adjacencyList = new int*[graphOrder];
	verticesDegrees = new int[graphOrder];
	visited = new bool[graphOrder];
	verticesColours = new int[graphOrder];
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

int Graph::GetGraphOrder() const
{
	return graphOrder;
}

int* Graph::DegreeSequence()
{
	int* degreeSequence = new int[graphOrder];
	for (int i = 0; i < graphOrder; i++)
	{
		degreeSequence[i] = verticesDegrees[i];
	}
	for (int i = graphOrder - 1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (degreeSequence[j] < degreeSequence[j + 1])
			{
				int temp = degreeSequence[j + 1];
				degreeSequence[j + 1] = degreeSequence[j];
				degreeSequence[j] = temp;
			}
		}
	}
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

int Graph::GraphComplementsEdgesNumber()
{
	int completeGraphEdgesNumber = graphOrder * (graphOrder - 1) / 2;
	int thisGraphEdgesNumber = 0;
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
