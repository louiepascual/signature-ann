/**
  Input Data Preparation
  genData.cpp

  Purpose: 
  Separates input data into a 60% training set and 40% verification set

  Input:
  File containing extracted pixel values with author ID

  Output:
  Generates 2 files: a training set and a validation set.

  @author Arazas, Al Jamil L. (2012-1-0712)
  @author Pascual, Louie Lester E. (2013-1-1743)
  @author Valeros, John Dinnex M. (2013-1-1618)

  @version 1.0 07/26/2016
**/

#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;
#define datatype double

vector< vector<datatype> > dataset;
ofstream foutTraining("training.in");
ofstream foutTest("test.in");
int NCOLS;

void divide();

int main(int argc, char **argv)
{
	// Check command usage
	if (argc != 2) {
    	cerr << "usage: " << argv[0] << " dataFile" << endl;
    	return -1;
  	}
	
	// Setup input files
	string dataFile;
	dataFile = argv[1];

	// Setup input filestream
	ifstream fin;
	fin.open(dataFile.c_str());

	// Ask for number of columns
	cout << "Enter number of columns: ";
	cin >> NCOLS;

	vector <datatype> tempV;
	int pUserNo = 1;
	int cUserNo = 1;
	vector <datatype> data;
	datatype t;
	while (fin >> t) {
		data.push_back(t);

		// Get Attributes
		for (int i = 1; i<NCOLS-1; i++){
			fin >> t;
			data.push_back(t);
		}

		// Get Target-Attribute
		fin >> cUserNo;
		data.push_back(cUserNo);

		// Divide only when author ID changes
		if (cUserNo == pUserNo)	{
			dataset.push_back(data);
			data.clear();
		}
		else {
			tempV = data;
			pUserNo = cUserNo;
			
			divide();

			data.clear();
			dataset.clear();
			dataset.push_back(tempV);
			tempV.clear();

		}
	}
	
	divide();

	return 0;
}

/**
Randomly divides the dataSet into a 60:40 ratio

Input: none
Output: none
**/
void divide()
{
    
	int half = round(dataset.size() * 0.4);
	cout << dataset.size()-half << " " << half << endl;
	
	// Per set of signatures of an author,
	// transfer an instance until 40% data is left
	while (dataset.size()>half)
	{
		int size = dataset.size();
		srand (time(NULL));
		int randNum = rand() % size; //0 to size-1

		for (int i = 0; i < NCOLS-1;i++)
			foutTraining << dataset[randNum][i]<<" ";
		foutTraining<<dataset[randNum][NCOLS-1]<<endl;

		dataset.erase(dataset.begin() + randNum);
	}

	for (int i = 0; i < dataset.size();i++)
	{
		for (int j = 0; j< NCOLS-1; j ++)
			foutTest<<dataset[i][j]<<" ";
		foutTest<<dataset[i][NCOLS-1]<<endl;
	}
}