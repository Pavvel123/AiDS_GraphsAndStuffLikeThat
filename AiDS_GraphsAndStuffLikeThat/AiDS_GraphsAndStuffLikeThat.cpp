#include <iostream>
#include "Graph.h"

int main()
{
    int graphsNumber = 0;
    std::cin >> graphsNumber;
	for (int w = 0; w < graphsNumber; w++)
	{
		Graph* g = new Graph();
		long long graphOrder = g->GetGraphOrder();

		int* degreeSequence = g->DegreeSequence();
		for (int i = 0; i < graphOrder; i++)
		{
			std::cout << degreeSequence[i] << ' ';
		}
		delete[] degreeSequence;

		std::cout << '\n' << g->NumberOfComponents() << '\n';

		std::cout << (g->IsBipartite() ? 'T' : 'F') << '\n';

		for (int i = 0; i < 2; i++)
		{
			std::cout << "?\n";
		}

		int* verticesColoursGreedy = g->VerticesColoursGreedy();
		for (int i = 0; i < graphOrder; i++)
		{
			std::cout << verticesColoursGreedy[i] << ' ';
		}
		delete[] verticesColoursGreedy;
		std::cout << '\n';

		for (int i = 0; i < 3; i++)
		{
			std::cout << "?\n";
		}

		std::cout << g->GraphComplementsEdgesNumber() << '\n';
		delete g;
	}
}