#include <iostream>
#include "AdjacencyMatrix.h"
#include <fstream>
#include <string>

using namespace std;
AdjacencyMatrix::AdjacencyMatrix(string fileName)
{
	fstream file;
	string str;
	file.open(fileName, ios::in);
	if (file.eof()) throw out_of_range("file is empty");
	getline(file, str); // count cities
	sizeMatrix = atoi(str.c_str());
	Matrix = new int* [sizeMatrix];
	for (int i = 0; i < sizeMatrix; i++)
		Matrix[i] = new int[sizeMatrix];
	for (int i = 0; i < sizeMatrix; i++)
		for (int j = 0; j < sizeMatrix; j++)
		{
			if (i == j) Matrix[i][j] = 0; // cityA -> cityA = 0
			else Matrix[i][j] = INT16_MAX;
		}
	Cities = new string[sizeMatrix];
};
unsigned int AdjacencyMatrix::findCity(string City)
{
	for (unsigned int i = 0; i < sizeMatrix; i++)
	{
		if (Cities[i] == City) return i;
	}
	return -1;
}
unsigned int AdjacencyMatrix::findNewIndex(string City)
{
	for (unsigned int i = 0; i < sizeMatrix; i++)
	{
		if (Cities[i] == "") return i;
	}
}
void AdjacencyMatrix::createMatrix(string fileName)
{
	fstream file;
	file.open(fileName, ios::in);
	if (file.eof()) throw out_of_range("file is empty");
	string str;
	getline(file, str); // size

	while (!file.eof())
	{
		string CityA, CityB;
		unsigned int IndexA, IndexB;
		string AB, BA;
		getline(file, str);
		unsigned int i = 0;
		///////////////////////////////////////////////////////////////// city A
		while (str[i] != ';')
		{
			CityA.push_back(str[i]);
			i++;
		} 
		i++;
		if (findCity(CityA) == -1)
		{
			IndexA = findNewIndex(CityA);
			Cities[IndexA] = CityA;
		}
		else
		{
			IndexA = findCity(CityA);
			Cities[IndexA] = CityA;
		}
		if (i >= str.length()) throw out_of_range("incorrect input");
		///////////////////////////////////////////////////////////////// city B
		while (str[i] != ';')
		{
			CityB.push_back(str[i]);
			i++;
		} 
		i++;
		if (findCity(CityB) == -1)
		{
			IndexB = findNewIndex(CityB);
			Cities[IndexB] = CityB;
		}
		else
		{
			IndexB = findCity(CityB);
			Cities[IndexB] = CityB;
		}
		if (i >= str.length()) throw out_of_range("incorrect input");
		///////////////////////////////////////////////////////////////// AB
		while (str[i] != ';')
		{
			AB.push_back(str[i]);
			i++;
		} 
		i++;
		if (AB == "N/A") Matrix[IndexA][IndexB] = INT16_MAX;
		else Matrix[IndexA][IndexB] = atoi(AB.c_str());
		if (i >= str.length()) throw out_of_range("incorrect input");
		///////////////////////////////////////////////////////////////// BA
		while (i < str.length())
		{
			BA.push_back(str[i]);
			i++;
		}
		if (BA == "N/A") Matrix[IndexB][IndexA] = INT16_MAX;
		else Matrix[IndexB][IndexA] = atoi(BA.c_str());
	}
	for (int i = 0; i < sizeMatrix; i++)
	{
		for (int j = 0; j < sizeMatrix; j++)
		{
			if (Matrix[i][j] == INT16_MAX) { cout << "inf "; }
			else cout << Matrix[i][j] << " ";
		}
		cout << endl;
	}
}
int minimum(int* array, int size)
{
	int min = INT16_MAX;
	for (int i = 0; i < size; i++)
	{
		if (array[i] < min) min = array[i];
	}
	return min;
}
unsigned int AdjacencyMatrix::Bellman_Ford(string cityA, string cityB)
{
	int* minWay = new int[sizeMatrix];
	int* labels = new int[sizeMatrix];
	for (unsigned int i = 0; i < sizeMatrix; i++)
	{
		minWay[i] = INT16_MAX;
	}minWay[findCity(cityA)] = 0;
	for (unsigned int k = 1; k < sizeMatrix; k++)
	{
		for (unsigned int i = 0; i < sizeMatrix; i++)
		{
			for (unsigned int j = 0; j < sizeMatrix; j++)
			{
				labels[j] = minWay[j] + Matrix[j][i];
			}
			minWay[i] = minimum(labels, sizeMatrix);
			for (unsigned int j = 0; j < sizeMatrix; j++)
				labels[j] = INT16_MAX;
		}
	}
	/*for (unsigned int j = 0; j < sizeMatrix; j++)
	cout << minWay[j] << endl;*/
	if (minWay[findCity(cityB)] == INT16_MAX)
	{
		cout << endl << "There is no way from " << Cities[findCity(cityA)] << " to " << Cities[findCity(cityB)];
		return 0;
	}
	else
	{
		cout << endl << "The optimal way from " << Cities[findCity(cityA)] << " to " << Cities[findCity(cityB)] << " is " << minWay[findCity(cityB)];
		return minWay[findCity(cityB)];
	}
}