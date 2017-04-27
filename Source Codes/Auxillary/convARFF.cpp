/**
  Coverts a dataset to an ARFF file
  convARFF.cpp

  Description:
  The dataset produced by the feature extraction process will be
  converted to an ARFF file so that the program Weka could use it.
**/  
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Change this to the desired file name of the ARFF file
#define ARFF "08x04_bin_shi00.arff"

// Change this to the path of the dataset file
#define PATH "64x32_bin_forged.in"

// Change this to the number of features of the dataset
#define feats 2048

int main() {
	ofstream fout(ARFF);

	fout << "@RELATION ";
	fout << ARFF << "\n\n";

	for(int i=1; i<=feats; i++) {
		fout << "@ATTRIBUTE f" << i << " NUMERIC\n"; 
	}	

	fout << "@ATTRIBUTE class {1,2,3,4,6,7,8,9,10,11,12,14,15,16,17,18,19,20,21,22,23,24,26,27,28,29,30,31,33,35,37,39,41,42,43,44,45,46,47,49,51,53,54,55,56,58,59,62,63,64,66,67,68,69,70,71,72,73,74,75,77,79,80,83,84,85,86,88,89,90,91,92,93,94,96,97,98,99,100}\n\n";
	fout << "@DATA\n";

	ifstream fin(PATH);

	string m;
	while(getline(fin,m)) {
		istringstream ss(m);

		double n;
		ss >> n;
		fout << n;
		while(ss >> n) {
			fout << ", ";
			fout << n;
		}
		fout << "\n";
	}
}
