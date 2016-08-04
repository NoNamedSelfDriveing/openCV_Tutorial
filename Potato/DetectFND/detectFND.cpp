#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>

using namespace std;
using namespace cv;

Mat img; Mat templ; Mat result;
char* image_window = "Source Image";
char* result_window = "Result window";
string fileName;

int match_method;
int max_Trackbar = 5;

void MatchingMethod( int, void* );

int main( int argc, char** argv )
{
    img = imread( argv[1], IMREAD_COLOR );
    GaussianBlur(img, img, Size(7, 7), 2, 2);
    cvtColor(img, img, COLOR_BGR2GRAY);

    namedWindow( image_window, CV_WINDOW_NORMAL );
    namedWindow( result_window, CV_WINDOW_NORMAL );

    char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
    createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );

    MatchingMethod( 0, 0 );
    return 0;
}

void MatchingMethod( int, void* )
{
    char fileName[1024];
    int num;
    for(num = 0; num < 10; num++){
        sprintf(fileName, "%d.png", num);
        templ = imread(fileName, IMREAD_COLOR);
    
        cvtColor(templ, templ, COLOR_RGB2GRAY);
        Mat img_display;
        img.copyTo( img_display );

        int result_cols =  img.cols - templ.cols + 1;
        int result_rows = img.rows - templ.rows + 1;

        result.create( result_rows, result_cols, CV_32FC1 );

        matchTemplate( img, templ, result, match_method );
        normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

        double minVal = 0; double maxVal = 0; 
        Point minLoc; Point maxLoc;
        Point matchLoc;

        minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
        if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
        { matchLoc = minLoc; }
        else
        { matchLoc = maxLoc; }

        rectangle( img, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
        rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );

        imshow( image_window, img );
        imshow( result_window, result );

        cout << num << endl;
        if( waitKey(0) >= 30);
    }
    return;
}
