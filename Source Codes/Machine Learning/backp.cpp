/**
  Backpropagation Algorithm (ANN Model Generation)
  backp.cpp

  Description:
  Uses the backpropagation algorithm to learn the weights of an
  Artificial Neural Network.

  Input:
  A training set, wherein the last column is the target-attribute.

  Output:
  Generates the weights of the network and is stored in a file.

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

// Change this to the number of instances in training set
#define numRecs 2820

// Change this to the desired path of output weights
#define PATH "64x32_sca_shi15_weight.in"

using namespace std;

struct data {
  double x[NI];
  double t[NT];
};

data D[numRecs];

// OUTPUT WEIGHTS
void outputWeightsToFile(double w[][N]) {
  // change argument to desired output filename
  ofstream fout(PATH);
  for(int j=0; j<N; j++) {
    for(int i=0; i<N; i++)
      fout << w[j][i] << " ";
    fout << endl;
  }
}

/**
Maps a given value using the sigmoid function

@param, the value to be mapped
@return, the resulting value
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

/**
Randomizes the value of the weights in the network

@param, the weights to be randomized
*/
void setRandom(double w[][N]) {
  for (int j = 0; j < N; j++)
    for (int i = 0; i < N; i++) 
      w[j][i] = double((rand() % 201) - 100) / 1000;
}

/**
Sets all values of the weights in the network to zero
@param, the weights to be set
*/
void setZero(double w[][N]) {
  for (int j = 0; j < N; j++)
    for (int i = 0; i < N; i++) 
      w[j][i] = 0.0;
}

/**
Train the network by calibrating the weights
using the backpropagation algorithm

@param, convergence rate
@param, initial set of weights
*/
void backpropagate(double h, double w[][N]) {
  double x[N];
  static double dw[N][N];
  double t[NT];
  double delta[N];
  setRandom(w);
  for (int z = 0; z < ITERS; z++) {
    for (int r = 0; r < numRecs; r++) {
      // initalize compute units
      for (int i = 0; i < NI; i++)
        x[i] = D[r].x[i];
       
      // initialize target units
      for (int i = 0; i < NT; i++)
        t[i] = D[r].t[i];

      // 1. process compute units
      computeNetwork(w,x);

      // 2. compute delta of output units
      for(int i=NI+NH, j=0; i<N; i++,j++) {
        delta[i] = x[i] * (1-x[i]) * (t[j] - x[i]);
      }
      
      // 3. compute delta of hidden units
      for(int i=NI; i<NI+NH; i++) {
        double s = 0.0;
        for(int j=NI+NH; j<N; j++) {
          s += w[j][i] * delta[j];
        }
        delta[i] = x[i] * (1 - x[i]) * s;
      }

      // 4. update the weights
      for (int j = 0; j < N; j++) 
        for (int i = 0; i < N; i++) {
          dw[j][i] = h * delta[j] * x[i];
          w[j][i]  = w[j][i] + dw[j][i]; 
        }
    }

    // Prompt which how many iterations have been done
    cout << "FINISHED ITER #" << z+1 << endl;
  }
}

int main(int argc, char **argv) {  
  // Check command usage
  if (argc != 2) {
      cerr << "usage: " << argv[0] << " trainingFile" << endl;
      return -1;
    }
  
  // Setup input files
  string trainingFile;
  trainingFile = argv[1];

  // Get and Set Input Training Data
  ifstream fin;
  fin.open(trainingFile.c_str());

  for(int i=0; i<numRecs; i++) {
    D[i].x[0] = 1.0; // bias unit

    // get attributes
    for(int j=1; j<NI; j++)
      fin >> D[i].x[j];

    // get target attribute
    int tAttr;
    fin >> tAttr;
    D[i].t[tAttr] = 1;
  }

  fin.close();

  // initialize weight array
  static double w[N][N];
  setZero(w);
  backpropagate(0.3, w);

  // output weights to file
  outputWeightsToFile(w);
  
}
