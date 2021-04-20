#include "pch.h"
#include "CppUnitTest.h"
#include "../graphs/AdjacencyMatrix.h"
#include "../graphs/AdjacencyMatrix.cpp"
#include <string>
#define TEST_CASE_DIRECTORT GetDirectoryName(__FILE__)
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

string GetDirectoryName(string path)
{
	const size_t last_slash_idx = path.rfind('\\');
	if (std::string::npos != last_slash_idx)
	{
		return path.substr(0, last_slash_idx + 1);
	}
	return "";
}

namespace TestGraphs
{
	TEST_CLASS(TestGraphs)
	{
	public:
		TEST_METHOD(OPEN_FILE)
		{
			string fileName = string(TEST_CASE_DIRECTORT) + "test1.txt";
			AdjacencyMatrix* Matrix = new AdjacencyMatrix(fileName);
			Matrix->createMatrix(fileName);
		}
		TEST_METHOD(not_find_file)
		{
			string fileName = string(TEST_CASE_DIRECTORT) + "netytakogo.txt";
			try
			{
				AdjacencyMatrix* Matrix = new AdjacencyMatrix(fileName);
			}
			catch (std::out_of_range error)
			{
				Assert::AreEqual("file is empty", error.what());
			}
		}
		TEST_METHOD(incorrect_input)
		{
			string fileName = string(TEST_CASE_DIRECTORT) + "test2.txt";
			try
			{
				AdjacencyMatrix* Matrix = new AdjacencyMatrix(fileName);
			}
			catch (std::out_of_range error)
			{
				Assert::AreEqual("incorrect input", error.what());
			}
		}
		TEST_METHOD(findCitiesTest)
		{
			string fileName = string(TEST_CASE_DIRECTORT) + "test1.txt";
			AdjacencyMatrix* Matrix = new AdjacencyMatrix(fileName);
			Matrix->createMatrix(fileName);
			Assert::AreEqual((int)0, (int)Matrix->findCity("01"));
			Assert::AreEqual((int)1, (int)Matrix->findCity("02"));
			Assert::AreEqual((int)2, (int)Matrix->findCity("03"));
			Assert::AreEqual((int)3, (int)Matrix->findCity("04"));
			Assert::AreEqual((int)4, (int)Matrix->findCity("05"));
		}
		TEST_METHOD(findWay)
		{
			string fileName = string(TEST_CASE_DIRECTORT) + "test1.txt";
			AdjacencyMatrix* Matrix = new AdjacencyMatrix(fileName);
			Matrix->createMatrix(fileName);
			Assert::AreEqual((int)6, (int)Matrix->Bellman_Ford("01", "03"));
		}
		TEST_METHOD(noWay)
		{
			string fileName = string(TEST_CASE_DIRECTORT) + "test1.txt";
			AdjacencyMatrix* Matrix = new AdjacencyMatrix(fileName);
			Matrix->createMatrix(fileName);
			Assert::AreEqual((int)0, (int)Matrix->Bellman_Ford("01", "05"));
		}
	};
}
