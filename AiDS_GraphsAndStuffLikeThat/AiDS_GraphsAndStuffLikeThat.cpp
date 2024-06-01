#include <iostream>
#include "Graph.h"

int main()
{
	int graphsNumber = 0;
	std::cin >> graphsNumber;
	for (int w = 0; w < graphsNumber; w++)
	{
		Graph g;
		long long graphOrder = g.GetGraphOrder();

		int* degreeSequence = g.DegreeSequence();
		for (int i = 0; i < graphOrder; i++)
		{
			std::cout << degreeSequence[i] << ' ';
		}
		delete[] degreeSequence;

		std::cout << '\n' << g.NumberOfComponents() << '\n';

		std::cout << (g.IsBipartite() ? 'T' : 'F') << '\n';

		std::cout << "?\n?\n";

		int* verticesColoursGreedy = g.VerticesColoursGreedy();
		for (int i = 0; i < graphOrder; i++)
		{
			std::cout << verticesColoursGreedy[i] << ' ';
		}
		delete[] verticesColoursGreedy;
		std::cout << '\n';

		int* verticesColoursLF = g.VerticesColoursLF();
		for (int i = 0; i < graphOrder; i++)
		{
			std::cout << verticesColoursLF[i] << ' ';
		}
		delete[] verticesColoursLF;

		std::cout << "\n?";

		//std::cout << '\n' << g.DifferentC4SubgraphsNumber() << '\n';
		std::cout << "\n?\n";

		std::cout << g.GraphComplementsEdgesNumber() << '\n';
		//delete g;
	}
}