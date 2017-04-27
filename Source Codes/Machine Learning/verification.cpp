/**
  Model Evaluation (ANN) - Signature Verification
  ver.cpp

  Description:
  Using the generated weights by backp.cpp 
  and a given validation set for signature verification

  Input:
  Weights and test file

  Output:
  A result file

  @author Arazas, Al Jamil L. (2012-1-0712)
  @author Pascual, Louie Lester E. (2013-1-1743)
  @author Valeros, John Dinnex M. (2013-1-1618)

  @version 1.0 09/22/2016
*/
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

#define ITERS 100

/* N nodes, NT targets, NH hidden, NI inputs */
// Change these according to preferred ANN design
#define N 3174
#define NT 101
#define NI 2049
#define NH 1024

// Change these to the number of instances in validation set
#define nTests 624

using namespace std;

// Setup stream for results text file
// change argument to desired output filename
ofstream fout("64x32_bin_forged_res2.out");

// READ THE WEIGHTS
void readWeights(double w[][N]) {
  // change argument to the name of the weight file
  // generate by backp.cpp
  ifstream in("weights2/64x32_bin_shi05_weight.in");
  for(int j=0; j<N; j++)
    for(int i=0; i<N; i++)
      in >> w[j][i];
}

/**
Sigmoid function

@param, value
@return, double value
*/
double sigmoid(double y) {
  return (1.0 / (1.0 + exp(-y)));
}

/**
Calculates the values of the nodes given the weights
and an initial values of the input layer nodes

@param, weights of the edges in the network
@param, the value in each node in the network
@return, none
*/
void computeNetwork(double w[][N], double x[]) {
  // compute the units in the hidden layer
  for(int i=NI; i<NI+NH; i++) {
    double s=0.0;

    // traverse through all the nodes in input layer
    for(int j=0; j<NI; j++) {
      s += w[i][j] * x[j];
    }
    x[i] = sigmoid(s);
  }

  // compute the units in the target layer
  for(int i=NI+NH; i<N; i++) {
    double s=0.0;

    // traverse through all the nodes in hidden layer
    for(int j=NI; j<NI+NH; j++) {
      s += w[i][j] * x[j];
    }
    x[i] = sigmoid(s);
  }
}

int main(int argc, char **argv) {  
  // Check command usage
  if (argc != 2) {
      cerr << "usage: " << argv[0] << " testFile" << endl;
      return -1;
    }

  // Read Weights
  static double w[N][N];
  readWeights(w);
  
  // Setup input files
  string testFile;
  testFile = argv[1];

  // Setup Test Data
  ifstream fin;
  fin.open(testFile.c_str());

  int numCorrect = 0, numIncorrect = 0, numPopulation = 0;
  double x[N];
  double matches[101][2] = {0};
  for(int i=0; i<nTests; i++) {
    memset(x,0.0,sizeof(x));
    x[0] = 1.0; // initialize bias unit
    
    // get the attributes
    for(int j=1; j<NI; j++)
      fin >> x[j];

    // get the correct output
    int actual, prediction;
    fin >> actual;

    computeNetwork(w,x);

    // search for max value
    double maxval = -1;
    int maxind = NI+NH;
    for(int j=NI+NH+1; j<N; j++) {
      if(x[j] > maxval) {
        maxval = x[j];
        maxind = j;
      }
    }

    // check correctness
    prediction = maxind-(NI+NH);
    if(prediction == actual) {
      numCorrect++;
      matches[actual][0]++;
    }
    else {
      numIncorrect++;
      matches[actual][1]++;
      fout << "PREDICTED: \t" << prediction << endl;
      fout << "ACTUAL: \t" << actual << "\n\n";
    }

    numPopulation++;
  }

  // output results
  fout << "Matched Forgeries: " << numCorrect << endl;
  fout << "Matched with Others : " << numIncorrect << endl;
  fout << "False Acceptance Rate: " << numIncorrect / (double)numPopulation << endl;


  // output matching table
  for(int i=1; i<101; i++) {
    fout << "i" << i << "\t";
    fout << matches[i][0] << "\t";
    fout << matches[i][1] << endl;    
  }


  
}
