#include <iostream>
#include <fstream>
#include "AdjacencyMatrix.h"


int main()
{
	string fileName = "in.txt";
	AdjacencyMatrix* Matrix = new AdjacencyMatrix(fileName);
	Matrix->createMatrix(fileName);
	Matrix->Bellman_Ford("01","03");
}
