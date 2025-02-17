/*
Latency testing for GStreamer pipeline, three camera output.
*/
#include <iostream>
#include <opencv2/opencv.hpp>
#include <time.h>

using namespace std;
using namespace cv;

int main() {
        VideoCapture cap1("nvcamerasrc sensor-id=1 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER);

        VideoCapture cap2("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER);

        VideoCapture cap3("nvcamerasrc sensor-id=2 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER);

        if(!cap1.isOpened()){
                cout << "Connection cap1 failed" << endl;
                return -1;
        }

        if(!cap2.isOpened()){
                cout << "Connection cap2 failed" << endl;
                return -1;
        }

        if(!cap3.isOpened()){
                cout << "Connection cap3 failed" << endl;
                return -1;
        }
 
	
	Mat frame1, frame2, frame3;

	while(1) {
		timespec begin, end;
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);

		cap1 >> frame1;
		cap2 >> frame2;
		cap3 >> frame3;

		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

		putText(frame1, format("Latency = %f sec",(long long) (end.tv_sec-begin.tv_sec) + (end.tv_nsec-begin.tv_nsec)/1e9), Point(30, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,0,255));
		putText(frame2, format("Latency = %f sec",(long long) (end.tv_sec-begin.tv_sec) + (end.tv_nsec-begin.tv_nsec)/1e9), Point(30, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,0,255));
		putText(frame3, format("Latency = %f sec",(long long) (end.tv_sec-begin.tv_sec) + (end.tv_nsec-begin.tv_nsec)/1e9), Point(30, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,0,255));

		imshow("Display1", frame1);
		imshow("Display2", frame2);
		imshow("DIsplay3", frame3);
		waitKey(1);
	}

	return 0;
}
