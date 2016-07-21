#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

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

    destroyWindow("Display Potato");
    return 0;
}
