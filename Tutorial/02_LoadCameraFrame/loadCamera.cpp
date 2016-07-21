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

    Mat edges;
    namedWindow(WindowName,1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        imshow(WindowName, frame);
        if(waitKey(30) >= 0) break;
    }

    destroyWindow(WindowName);
    return 0;
}
