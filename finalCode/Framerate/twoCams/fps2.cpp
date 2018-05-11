/*
Frame rate testing, two camera output.
*/
#include <iostream>
#include <ctime>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main() {
	VideoCapture cap1("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER);
	
	VideoCapture cap2("nvcamerasrc sensor-id=2 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER);

	if(!cap1.isOpened()){
		cout << "Connection cap1 failed" << endl;
		return -1;	
	}

	if(!cap2.isOpened()){
		cout << "Connection cap2 failed" << endl;
		return -1;
	}

	double fps = cap1.get(CV_CAP_PROP_FPS);
	cout << "Frames per second using get : " << fps << endl;

	int num_frame = 120;
	time_t start, end;
	int key = 0;
	Mat frame1, frame2;

	time(&start);

	for(int i = 0; i < num_frame; i++) 
	{
		cap1 >> frame1;
		cap2 >> frame2;
		
		imshow("Display1", frame1);
		imshow("Display2", frame2);

		waitKey(1);
	}

	time(&end);

	double seconds = difftime (end, start);
	fps = num_frame / seconds;
	cout << "Estimated frames per second : " << fps << endl;

	return 0;
}
