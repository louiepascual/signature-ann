/**
  Model Evaluation (ANN) - Signature Recognition
  res.cpp

  Description:
  Using the generated weights by backp.cpp,
  measure the performance of the network
  with the use of a provided validation file

  Input:
  Weights and test file

  Output:
  A computation of its correctly classified instances, the incorrect ones, and its accuracy.

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

// Change this to the path of the weight file
#define WGHTSPATH "weights2/64x32_bin_shi05_weight.in"

// Change this to the desired path where the results will be saved
#define RESPATH "64x32_bin_shi00_res.out"

using namespace std;

// Setup stream for results text file
// change argument to desired output filename
ofstream fout(RESPATH);

// READ THE WEIGHTS
void readWeights(double w[][N]) {
  // change argument to the name of the weight file
  // generate by backp.cpp
  ifstream in(WGHTSPATH);
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
  double cm[101][101]= {0}; // confusion matrix
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
    }
    else {
      numIncorrect++;
      fout << "PREDICTED: \t" << prediction << endl;
      fout << "ACTUAL: \t" << actual << "\n\n";
    }


    // adjust confusion matrix
    cm[actual][prediction]++;

    numPopulation++;
  }

  // compute precision, recall, and f-measure
  double precision = 0;
  double recall = 0;
  double fscore = 0;
  double accuracy = 0;
  for(int i=1; i<101; i++) {
    double tp, fp, fn;

    // get true positive of ith class
    tp = cm[i][i]; 

    // get false positives of ith class
    fp = 0;
    for(int j=1; j<101; j++) {
      if(j != i)
        fp += cm[j][i];
    }

    // get false negatives of ith class
    fn = 0;
    for(int j=1; j<101; j++) {
      if(j != i)
        fn += cm[i][j];
    }
    
    // some id's are not part of the dataset, 
    // so its computation should be ignored
    if((tp + fp) != 0) 
      precision += (tp / (tp + fp));
    
    if((tp + fn) != 0)
      recall += (tp / (tp + fn));
  }

  // compute average precision/recall 
  accuracy = (numCorrect/(double)numPopulation);
  precision = precision / 79.0;
  recall = recall / 79.0;

  // compute Fmeasure
  double beta = 1;
  fscore = ((beta * beta) + 1) * precision * recall;
  fscore = fscore / (((beta * beta) * precision) + recall);

  // Output Confusion Matrix
  for(int i=0; i<101; i++) {
    for(int j=0; j<101; j++) {
      fout << cm[i][j] << " ";
    }
    fout << endl;
  }
  
  // output results
  fout << "Correct Instances: " << numCorrect << endl;
  fout << "Incorrect Instances: " << numIncorrect << endl;
  fout << "Accuracy: " << accuracy << endl;
  fout << "Average Precision: " << precision << endl;
  fout << "Average Recall: " << recall << endl;
  fout << "Fscore: " << fscore << endl;
  
}
