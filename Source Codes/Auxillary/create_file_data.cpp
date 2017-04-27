/**
  Create Text File Data
  create_file_data.cpp

  Description:
  Here is where the scalar and binary datasets are generated
**/
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstdlib>

#define PATH "C:/" // NOTE: PATH may change depending on where the to be processed are stored

using namespace cv;
using namespace std;



int main(int, char** argv) //NOTE: Program takes a parameter of 1 file which consists of all the file names.
{
    for (int a1 = 0; a1 < 5; a1++)      //NOTE: these three loops are created for convenience so that you can convert multiple sets in one run. Most of these just changes the PATH of the file. The values in these loops can be changed if neccessary.
    {
        for (int a2 = 0; a2 < 4; a2++)
        {
            for (int a3 = 0; a3 <3; a3++)
            {

    string psize="";
    string dir = "";
    string dim = "";
    int maxsize;

    switch (a1)
    {
    case 0:
        dim = "128x64";
        maxsize = 128;
        break;
    case 1:
        dim = "64x32";
        maxsize = 64;
        break;
    case 2:
        dim = "32x16";
        maxsize = 32;
        break;
    case 3:
        dim = "16x8";
        maxsize = 16;
        break;
    case 4:
        dim = "8x4";
        maxsize = 8;
        break;
    }

    switch (a2)
    {
    case 0:
        dir = "up";
        break;
    case 1:
        dir = "down";
        break;
    case 2:
        dir = "left";
        break;
    case 3:
        dir = "right";
        break;
    }

    switch (a3)
    {
    case 0:
        psize = "5px";
        break;
    case 1:
        psize = "10px";
        break;
    case 2:
        psize = "15px";
        break;
    }

    cout<<dim<<" - "<<dir<<" - "<<psize<<endl;


    Mat src, dst;
    ifstream fin(argv[1]);

    string loc = PATH+psize+"/"+dir+"/"+dim+"/scaled.out";
    string loc2 = PATH+psize+"/"+dir+"/"+dim+"/binarized.out";


    ofstream fout(loc.c_str());
    ofstream fout2(loc2.c_str());
    while (!fin.eof())
    {

    string mysrc,filename;
    fin>>filename;

    mysrc = PATH+psize+"/"+dir+"/"+dim+"/"+filename;

    src = imread( mysrc, IMREAD_COLOR );


    cvtColor(src, src, CV_RGB2GRAY);

    string q = filename.substr(9,3);
    vector <double> temp;

    cout<<q<<endl;
    int c =maxsize;
    int r =c/2;

    for (int i = 0 ; i < r*c; i++)
        temp.push_back(0);

        int tempit=0;

    for (int x = 0; x < src.cols;x++)
    {
        for (int y=0;y<src.rows;y++)
        {
            vector <Scalar> intensityT ;
                    temp[tempit] += src.at<uchar>(y, x);
                    tempit++;

        }
    }

    for (int i = 0; i < r*c; i++)
    {



        double num = (255-temp[i])/255.0;
        fout<<num<<" ";


        if (num<0.125)
        fout2<<0<<" ";
        else fout2<<1<<" ";


    }

    fout<<q<<endl;
    fout2<<q<<endl;

    }
    }}} // } of 3 outer loops
}
