/**
  Shift Pixels
  shift_pixels.cpp

  Description:
  Shifts the pixels in an image to either left, right, up, or down
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

Mat src, dst;


 Mat translateImg(Mat &img, int offsetx, int offsety){
    Mat trans_mat = (Mat_<double>(2,3) << 1, 0, offsetx, 0, 1, offsety);
    warpAffine(img,img,trans_mat,img.size(),INTER_LINEAR,BORDER_CONSTANT,Scalar(255,255,255));
    return trans_mat;
}


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



        translateImg(src,10,0); 
        /*  2nd parameter is the shift on x axis. 
            positive - right
            negative - left
            3rd parameter is the shift on y axis.
            positive - up
            negative - down
        */




 imwrite( PATH+"10px/right/"+filename, src ); // PATH can be changed, depending on where you want to save

}


  return 0;
}

