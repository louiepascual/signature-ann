/**
  Histogram Equalization
  histogram_eq.cpp

  Description:
  Applies histogram equalization to the images
**/

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <cmath>

#define PATH "C:/" // NOTE: PATH may change depending on where the to be processed are stored


using namespace cv;
using namespace std;


Mat src;



int main( int, char** argv ) //NOTE: Program takes a parameter of 1 file which consists of all the file names.
{

ifstream fin(argv[1]);
while (!fin.eof())
{

string mysrc,filename;
fin>>filename;
mysrc = PATH+filename;


  src = imread( mysrc, IMREAD_COLOR );
  
 
  cvtColor(src, src, CV_RGB2GRAY);



  if( src.empty() )
    {
      printf(" No data entered, please enter the path to an image file \n");
      return -1;
    }

    equalizeHist( src, src );

  imwrite( PATH+"histogramEq/"+filename, src ); // you can also change the path here for convenience

}

  return 0;
}

