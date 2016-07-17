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
    //namedWindow("test", 1);

    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        //imshow("test", edges);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        if(waitKey(30) >= 0) break;
    }

    cvDestroyWindow("edges");
    return 0;
}
/*
   int main(int argc, char** argv){
   string imageName("potato.jpg");

   if(argc > 1)
   {
   imageName = argv[1];
   }

   Mat image;
   image = imread(imageName.c_str(), IMREAD_COLOR);

   if( image.empty() )
   {
   cout << "Could not open or find the Image" << std::endl;
   return -1;
   }

   namedWindow("Display Potato", WINDOW_AUTOSIZE);
   imshow("Display Potato", image);

   waitKey(0);
   return 0;
   }
   */
