#pragma once
class Graph
{
private:
	int** adjacencyList;
	int* verticesDegrees;
	bool* visited;
	int* verticesColours;
	int graphOrder;

	void Dfs(int v);
	bool DfsCheck(int v, int colour);

public:
	Graph();

	int GetGraphOrder() const;

	int* DegreeSequence();
	int NumberOfComponents();
	bool IsBipartite();
	int* EccentricityOfVertices();
	bool IsPlanar();
	int* VerticesColoursGreedy();
	int* VerticesColoursLF();
	int* VerticesColoursSLF();
	int DifferentC4SubgraphsNumber();
	int GraphComplementsEdgesNumber();

	~Graph();
};