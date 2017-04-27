/**
  Center the signature
  center_image.cpp

  Description:
  Looks for the centroid of the signature, and use it as pivot to move the signature
  to the center of the image
**/
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <cmath>

#define PATH "C:/" //NOTE: PATH may change depending on where the to be processed are stored


using namespace cv;
using namespace std;


Mat src;
int top, bottom, left, right;

 Mat translateImg(Mat &img, int offsetx, int offsety){
    Mat trans_mat = (Mat_<double>(2,3) << 1, 0, offsetx, 0, 1, offsety);
    warpAffine(img,img,trans_mat,img.size(),INTER_LINEAR,BORDER_CONSTANT,Scalar(255,255,255));
    return trans_mat;
}


int main( int, char** argv )  //NOTE: Program takes a parameter of 1 file which consists of all the file names.
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

    double pX = 0;
    double pY = 0;
    double tX = 0;
    double tY = 0;
    double centerX[1024] = {0};
    double centerY[512] = {0};

    for (int x = 0; x < 1024; x++)
    {
        for (int y = 0; y < 512; y++)
        {
            Scalar intensity = src.at<uchar>(y, x);
            int toAdd = 0;
            if (intensity[0]<128) toAdd = 1; else toAdd = 0;
            centerX[x] += toAdd;
            centerY[y] += toAdd;
        }

    }

 

    for (int x = 0; x < 1024; x++)
    {
         pX += (centerX[x]*x);
         tX += centerX[x];
    }

    for (int y = 0; y < 512; y++)
    {
         pY += (centerY[y]*y);
         tY += centerY[y];
    }
    pX = pX/tX;
    pY = pY/tY;

    cout<< pX <<" "<<pY<<endl;
    pX = floor(pX);
    pY = floor(pY);


        translateImg(src,511-pX,255-pY);


}


  return 0;
}

