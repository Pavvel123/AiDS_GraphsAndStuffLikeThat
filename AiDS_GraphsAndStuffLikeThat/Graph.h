#pragma once
class Graph
{
private:
	int** adjacencyList;
	int* verticesDegrees;
	bool* visited;
	int* verticesColours;
	long long graphOrder;

	void Dfs(long long v);
	bool DfsCheck(long long v, long long colour);
	static void Merge(int* arr, int left, int mid, int right, int* arr2 = nullptr);
	void MergeSort(int* arr, int left, int right, int* arr2 = nullptr);

public:
	Graph();

	long long GetGraphOrder() const;

	int* DegreeSequence();
	int NumberOfComponents();
	bool IsBipartite();
	//int* EccentricityOfVertices();
	//bool IsPlanar();
	int* VerticesColoursGreedy();
	int* VerticesColoursLF();
	//int* VerticesColoursSLF();
	long long DifferentC4SubgraphsNumber() const;
	long long GraphComplementsEdgesNumber() const;

	~Graph();
};