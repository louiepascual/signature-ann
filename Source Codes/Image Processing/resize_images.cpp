/**
  Resize Images
  resize_images.cpp

  Description:
  Resize the images to 8x4, 16x8, 32x16, and 64x32
**/
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <cmath>

#define PATH "C:/" //NOTE: PATH may change depending on where the to be processed are stored
#define PATHDST8 "C:/resized/8x4/"
#define PATHDST16 "C:/resized/16x8/"
#define PATHDST32 "C:/resized/32x16/"
#define PATHDST64 "C:/resized/64x32/"
    /*
    NOTE:
    The Paths above may change depending on where you want to save.
    */


using namespace cv;
using namespace std;

Mat src, dst;

int main(int, char** argv) //NOTE: Program takes a parameter of 1 file which consists of all the file names.
{


    ifstream fin(argv[1]);
    while (!fin.eof())
    {

    string mysrc,filename;
    fin>>filename;
    mysrc = PATH+filename;

    src = imread( mysrc, IMREAD_COLOR );


    cvtColor(src, src, CV_RGB2GRAY);


    resize(src,dst,Size(8,4));
    imwrite( PATHDST8+filename, dst );

    resize(src,dst,Size(16,8));
    imwrite( PATHDST16+filename, dst );

    resize(src,dst,Size(32,16));
    imwrite( PATHDST32+filename, dst );

    resize(src,dst,Size(64,32));
    imwrite( PATHDST64+filename, dst );

   

    }
}
