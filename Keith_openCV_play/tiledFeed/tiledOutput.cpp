/*
	Two camera input -> output into one window/tiled
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>

using namespace std;
using namespace cv;

#define WIN_NAME "Tiled Video"

int main(int argc, char *argv[])
{
    const string
    Mat fr1, fr2, tile;
    namedWindow(WIN_NAME); // pre-create named window

	VideoCapture cap1("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw(memory:NVMM), format=(string)BGR ! videoconvert ! video/x-raw(memory:NVMM), format=(string)BGR ! appsink", CAP_GSTREAMER); //middle output

	VideoCapture cap2("nvcamerasrc sensor-id=2 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw(memory:NVMM), format=(string)BGR ! videoconvert ! video/x-raw(memory:NVMM), format=(string)BGR ! appsink", CAP_GSTREAMER); //output closest to center of board

	if(!cap1.isOpened()){
		cout << "connection cap1 failed" << endl;
		return -1;
	}

	if(!cap2.isOpened()){
		cout << "connection cap2 failed" << endl;
		return -1;
	}

    	while (true)
    	{
        	cap1 >> fr1;
       		cap2 >> fr2;
		//apply horizontal concatenation on inputs/matrices
		hconcat(fr1, fr2, tile);        	

        	imshow(WIN_NAME, tile);

        	if(waitKey(30) >= 0)
            		break;
    	}
    	return 0;
}
