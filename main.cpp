#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace cv;
using namespace std;


videocapture cap("C:/Users/elad2_000/Documents/Winter 2016 Courses/CSI4133/Assignment02/video/park.avi");

//loads the frames to be compared (in grayscale)
Mat frame1 = imread("/../images01/Img02_0076.bmp", CV_LOAD_IMAGE_GRAYSCALE);
Mat frame2 = imread("/../images01/Img02_0077.bmp", CV_LOAD_IMAGE_GRAYSCALE);
Mat frame3, frame4;
int tValue = 100;

//the function that is called when the tracker is moved
void callFunc(int, void*) {
	threshold(frame3, frame4, tValue, 255, THRESH_BINARY);
	imshow("Threshold Adjustment", frame4);
}

int main(int argc, const char** argv)
{
	//calculates the absolute difference between two frames
	absdiff(frame1, frame2, frame3);
	namedWindow("Threshold Adjustment", CV_WINDOW_AUTOSIZE);
	createTrackbar("Value", "Threshold Adjustment", &tValue, 255, callFunc);
	callFunc(0, 0);


	waitKey(0); //waits infinite amount of time for a keypress
	imwrite("C:/thresholdResult.bmp", frame4); //once a key is pressed, the program exits and saves the resulting image

	return 0;
}

