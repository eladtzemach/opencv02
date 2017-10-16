#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace cv;
using namespace std;
//
//Mat frame3, frame4;
//int tValue = 100;
//
////the function that is called when the tracker is moved
//void callFunc(int, void*) {
//	threshold(frame3, frame4, tValue, 255, THRESH_BINARY);
//	imshow("Threshold Adjustment", frame4);
//}
//
//int main(int argc, const char** argv)
//{
//
//	VideoCapture cap("C:/Users/elad2_000/Documents/Winter 2016 Courses/CSI4133/Assignment02/video/park.avi");
//	if (!cap.isOpened()) {
//		cout << "Cannot open the video file" << endl;
//		return -1;
//	}
//	int frm_count = cap.get(CAP_PROP_FRAME_COUNT);
//
//
//	Mat frame1;
//	cap.set(CAP_PROP_POS_FRAMES, 0);
//	cap >> frame1;
//	Mat frame2;
//	cap.set(CAP_PROP_POS_FRAMES, 1);
//	cap >> frame2;
//
//	//calculates the absolute difference between two frames
//	absdiff(frame1, frame2, frame3);
//	namedWindow("Threshold Adjustment", CV_WINDOW_AUTOSIZE);
//	createTrackbar("Value", "Threshold Adjustment", &tValue, 255, callFunc);
//	callFunc(0, 0);
//
//
//	switch (waitKey(0)) {
//	case 1048603:
//		Size framesize(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
//		VideoWriter output_cap("D:/out.avi", CV_FOURCC('D','I', 'V', '3'), cap.get(CV_CAP_PROP_FPS), framesize, 1);
//		for (int k = 0; k < frm_count; k++) {
//			cap.set(CAP_PROP_POS_FRAMES, k);
//			cap >> frame1;
//			cap.set(CAP_PROP_POS_FRAMES, k + 1);
//			cap >> frame2;
//			absdiff(frame1, frame2, frame3);
//			threshold(frame3, frame4, tValue, 255, THRESH_BINARY);
//			output_cap.write(frame4);
//		}
//		return 0;
//	}
//
//	return 0;
//	
//
//}

/**
* Name: Adnan Khan
* Student: 6362606
* Course: CSI4133
* Date: 12 February 2016
*
* Assignment 2
*
* OpenCV Version: 3.1
*
* Usage:
*
* To run: ./a2 <video path>
*
* To quit: ctrl+c in terminal
*          or will exit automatically once all frames have been processed.
*          result.avi will be saved to current working directory
*/









//using namespace std;
//using namespace cv;

int threshold_value = 21;
int const max_value = 255;

int main(int argc, char** argv) {

	//load source video
	VideoCapture cap("C:/Users/elad2_000/Documents/Winter 2016 Courses/CSI4133/Assignment02/video/park.avi");
	if (!cap.isOpened()) { printf("error loading video \n"); return -1; }

	namedWindow("Assignment 2", 1);

	Mat prev;
	Mat cur;
	Mat diff;

	cap >> prev;
	cvtColor(prev, prev, CV_RGB2GRAY);

	VideoWriter out("D:/out.avi", CV_FOURCC('D', 'I', 'V', '3'), cap.get(CAP_PROP_FPS), CvSize(prev.size()), true);

	if (!out.isOpened()) { printf("error opening VideoWriter \n"); return -1; }


	while (1) {
		cap >> cur;

		if (cur.data && prev.data) {
			cvtColor(cur, cur, CV_RGB2GRAY);
			absdiff(cur, prev, diff);
			threshold(diff, diff, threshold_value, max_value, 0);
			cvtColor(diff, diff, CV_GRAY2BGR);
			if (diff.data) {
				out.write(diff);
				imshow("Assignment 2", diff);
			}

			prev = cur.clone();

		}
		else {
			break;
		}

		if (waitKey(30) >= 0) break;

	}

	return 0;
}


