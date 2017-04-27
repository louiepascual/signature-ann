/**
  Image Padding and Resize
  image_padding_resize.cpp

  Description:
  Pads pixels until 2:1 ratio is met, then resize image to 1024 x 512
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

int borderType;
int ctr=0;

int main( int, char** argv ) //NOTE: Program takes a parameter of 1 file which consists of all the file names.
{

ifstream fin(argv[1]);
while (!fin.eof())
{

string mysrc,filename;
fin>>filename;
mysrc = PATH+filename;



  src = imread( mysrc, IMREAD_COLOR );
  

  if( src.empty() )
    {
      printf(" No data entered, please enter the path to an image file \n");
      return -1;
    }


    int pixels_needed;
    int top,left,bottom,right;

    float aspect_ratio = ceil((float)src.cols/(float)src.rows);


    cout << "on "<<filename<<endl;
    if (aspect_ratio > 2)
    {
        cout<< "aspect_ratio > 2 , width too long"<<endl<<"attempting to pad on height"<<endl;

        pixels_needed = ceil((float)src.cols/2 - src.rows);
        left = (int) 0; right = 0;
        top = pixels_needed/2; bottom = pixels_needed /2;

        if (pixels_needed%2==1)
        bottom++;

        if (src.cols%2==1)
        right++;
    }
    else
    {
        cout<< "aspect_ratio < 2 , height too long"<<endl<<"attempting to pad on width"<<endl;

        pixels_needed = src.rows*2-src.cols;


        top = (int) 0; bottom = 0;
        left = pixels_needed/2; right = pixels_needed /2;

        if (pixels_needed%2==1)
        right++;
    }


    int newW = src.cols+left+right;
    int newH = src.rows+top+bottom;
    cout<<"current size\t= "<<src.cols<<" x "<<src.rows<<endl;
    cout<<"aspect ratio\t= "<<aspect_ratio<<endl;
    cout<<"pixels added:"<<endl;
    cout<<"\t\ttop = "<<top<<endl;
    cout<<"\t\tbottom = "<<bottom<<endl;
    cout<<"\t\tleft = "<<left<<endl;
    cout<<"\t\tright = "<<right<<endl;
    cout<<"new size\t= "<<newW<<" x "<<newH<<endl;
    cout<<"new aspect ratio\t= "<<(float)newW/newH<<endl;
    cout<<"proceeding on resizing"<<endl;


    if ((float)newW/newH != 2.0)
    {
        cout <<"error on aspect ratio"<<endl;
        cout <<"new width = "<<newW<<endl;
        cout <<"new height = "<<newH<<endl;
        cout <<"aspect ratio = "<<(float)newW/newH<<endl;
        system("pause");
    }

    if (newW%2==1)
    {
        cout<<"error on newW"<<newW<<endl;
        system("pause");
    }




    cout<<"current size\t= "<<src.cols<<" x "<<src.rows<<endl;
    cout<<"aspect ratio\t= "<<aspect_ratio<<endl;
    cout<<"pixels added\tleft = "<<left<<endl<<"\t\tright = "<<right<<endl;
    cout<<"new size\t= "<<src.cols<<" x "<<src.rows+top+bottom<<endl;
    cout<<"new aspect ratio\t= "<<src.cols/(src.rows+top+bottom)<<endl;
    cout<<"proceeding on resizing"<<endl;



 dst = src;
 borderType = BORDER_REPLICATE;

 Scalar value( 255,255,255 );
 copyMakeBorder( src, dst, top, bottom, left, right, borderType, value );


 resize(dst,dst,Size(1024,512));
 imwrite( PATH+"1024x512/"+filename, dst ); // PATH here can also be changed to a specific path, depending on where you want to save

 cout<<"success"<<endl<<endl;

 ctr++;



}

cout<< ctr<<" files resized to 1024 x 512"<<endl;
  return 0;
}

