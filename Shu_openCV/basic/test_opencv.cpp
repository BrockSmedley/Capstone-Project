#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
	VideoCapture cap("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER);
	if(!cap.isOpened()){
		cout << "COnnection failed" << endl;
		return -1;	
	}
	Mat frame;
	while(1) {
		cap >> frame;
		imshow("Display window", frame);
		waitKey(1);
	
	}
	return 0;
}
