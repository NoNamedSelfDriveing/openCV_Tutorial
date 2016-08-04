#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <unistd.h>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

char WindowName[] = "Camera_Orig";

int main(){

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat Frame;
    Mat cvtFrame;
    Mat thresHold;
    Mat unique;
    Mat output;

    namedWindow("Origin", 1);
    namedWindow("cvtColor", 1);
    namedWindow("cvtColorUnique", 1);
    namedWindow("Threshold",1);

    for(;;)
    {
        cap >> Frame; // get a new frame from camera
        threshold(Frame, unique, 100, 255, CV_THRESH_BINARY);
        imshow("cvtColorUnique", unique);
        cvtColor(Frame, cvtFrame, COLOR_BGR2GRAY);
        threshold(cvtFrame, thresHold, 100, 255, CV_THRESH_BINARY);
        GaussianBlur(thresHold, output, Size(7,7), 0.001, 0.001);
        //서버 클라이언트 전송 사이 성능 비교 필요 : 해상도?
        imshow("Origin", Frame);
        imshow("cvtColor", cvtFrame);
        imshow("Threshold", output);
        if(waitKey(30) >= 0) break;
    }

    cvDestroyWindow("Origin");
    cvDestroyWindow("cvtColor");
    cvDestroyWindow("Threshold");
    cvDestroyWindow("cvtColorUnique");
    return 0;
}
