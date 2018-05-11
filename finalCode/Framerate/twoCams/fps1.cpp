/*
Frame rate testing, two camera output.
*/
#include <iostream>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

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


	int frameCounter = 0;	
	int tick = 0;
	int fps;
	int key = 0;
	time_t begin = time(0);
	Mat frame1, frame2;

	while(1) 
	{
		cap1 >> frame1;
		cap2 >> frame2;
		
		frameCounter++;
		time_t now = time(0) - begin;

		if(now - tick >= 1)
		{
			tick++;
			fps = frameCounter;
			frameCounter = 0;
		}

        	putText(frame1, format("Average FPS=%d", fps ), Point(30, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,0,255));		

        	putText(frame2, format("Average FPS=%d", fps ), Point(30, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,0,255));		
		
		imshow("Display1", frame1);
		imshow("Display2", frame2);
		waitKey(1);
	}
	return 0;
}
