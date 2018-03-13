/*
	Two camera input -> output into one window/tiled
*/

#include <opencv2/opencv.hpp>
#include <iostream>


using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    //Mat tile, matArray[3];
    Mat fr1, fr2, fr3, tile, matArray[3];

	VideoCapture cap1("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER); //middle output

	VideoCapture cap2("nvcamerasrc sensor-id=1 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER); //output closest to edge of board


	VideoCapture cap3("nvcamerasrc sensor-id=2 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER); //output closest to center of board
	
	if(!cap1.isOpened()){
		cout << "connection cap1 failed" << endl;
		return -1;
	}
	if(!cap2.isOpened()){
		cout << "connection cap2 failed" << endl;
		return -1;
	}
	if(!cap3.isOpened()){
		cout << "connection cap3 failed" << endl;
		return -1;
	}

    	while (true)
    	{
        	//cap1 >> fr1;
       		//cap2 >> fr2;
		//cap3 >> fr3;

		cv::Mat matArray[3] = {cv::Mat fr1(1, 3, CV_8UC1, cv::Scalar(1)),
			       cv::Mat fr2(1, 3, CV_8UC1, cv::Scalar(2)),
			       cv::Mat fr3(1, 3, CV_8UC1, cv::Scalar(3)),};

        	cap1 >> fr1;
       		cap2 >> fr2;
		cap3 >> fr3;

		cv::Mat tile;
		cv::hconcat(matArray, 3, tile);        	

        	imshow("Tiled Image", tile);

        	if(waitKey(30) >= 0) 
            		break;
    	}
    	return 0;
}
