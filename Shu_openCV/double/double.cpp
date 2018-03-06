#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
	VideoCapture cap1("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER);
	

	VideoCapture cap2("nvcamerasrc sensor-id=1 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER);

	if(!cap1.isOpened()){
		cout << "Connection cap1 failed" << endl;
		return -1;	
	}

	if(!cap2.isOpened()){
		cout << "Connection cap2 failed" << endl;
		return -1;
	}

	Mat gray;
	Mat frame1, frame2;
	while(1) {
		cap1 >> frame1;
		cap2 >> frame2;
		cvtColor(frame2, gray, CV_BGR2GRAY);
		
		GaussianBlur(gray, gray, Size(3 ,3 ), 0, 0);
		Mat dst1;
		Canny(gray, dst1, 50, 150, 3);
		imshow("Display1", frame1);
		imshow("Display2", dst1);
		waitKey(1);
	
	}





	return 0;
}
