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
    namedWindow("edges",1);

    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 0.001, 0.001);
        //서버 클라이언트 전송 사이 성능 비교 필요 : 해상도?
        imshow("edges", edges);
        if(waitKey(30) >= 0) break;
    }

    destroyWindow("edges");
    return 0;
}
