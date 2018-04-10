#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>

using namespace cv;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::duration<float> fsec;

int main() {
	VideoCapture cap1("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER);
	

	VideoCapture cap2("nvcamerasrc sensor-id=2 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER);

	if(!cap1.isOpened()){
		std::cout << "Connection cap1 failed" << endl;
		return -1;	
	}

	if(!cap2.isOpened()){
		std::cout << "Connection cap2 failed" << endl;
		return -1;
	}

	deque<double> frame_delas;
	int key = 0;
	int WINDOW_SIZE = 100;
	Mat frame1, frame2;

	while(1) 
	{
		auto start = Time::now();
		cap1 >> frame1;
		cap2 >> frame2;
		
		auto stop = Time::now();
		fsec duration = stop - start;
        	double fps = (1.0 / sec);
        	if (frame_delas.size() >= WINDOW_SIZE) frame_delas.pop_front();
        	frame_delas.push_back(fps);
		double avg_fps = accumulate(frame_delas.begin(), frame_delas.end(), 0.0) / frame_delas.size();

        	putText(frame1, format("Average FPS=%f", avg_fps ), Point(30, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,0,255));		

        	putText(frame2, format("Average FPS=%f", avg_fps ), Point(30, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,0,255));		
		
		imshow("Display1", frame1);
		imshow("Display2", frame2);

		waitKey(1);
		
	}


	return 0;
}
