#pragma once
#include <string>
using namespace std;
class AdjacencyMatrix
{
private:
	size_t sizeMatrix;
	int** Matrix;
	string* Cities;
public:
	AdjacencyMatrix(string); // creating a list WITHOUT data
	~AdjacencyMatrix() 
	{
		delete Matrix;
		delete Cities;
	};
	void createMatrix(string);
	unsigned int Bellman_Ford(string A, string B);
	unsigned int findNewIndex(string);
	unsigned int findCity(string);
};