#include "opencv2/opencv.hpp"
#include <iostream>
#include <highgui.h>
#include <unistd.h>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap(0);

    Mat original;   // 원본을 담을 공간
    Mat convert;    // 회색으로 변환할 이미지를 담을 공간
    Mat output;     // 회색으로 변환한 이미지를 이진화하여 이미지를 담는 공간

    namedWindow("ORIGINAL", 1); // 원본을 띄워주는 창
    namedWindow("CONVERT", 1);  // 변환된 이미지를 띄워주는 창
    namedWindow("OUTPUT", 1);   // 이진화된 이미지를 띄워주는 창

    while(1)
    {
        cap >> original; 

        cvtColor(original, convert, CV_BGR2GRAY);  // original을 회색으로 변환한 것을 convert에 대입
        imshow("ORIGINAL", original);  // 화면 띄워주기
        imshow("CONVERT", convert);    // 화면 띄워주기

        threshold(convert, output, 100, 255, CV_THRESH_BINARY);  // convert를 threshold 함수를 통해 이진화 한 후 output에 대입

        imshow("OUTPUT", output);  // 화면 띄워주기
        waitKey(1);
    }

}
