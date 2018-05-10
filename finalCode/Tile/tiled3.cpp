/*
	Two camera input -> output into one window/tiled
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat fr1, fr2, fr3, tile, out, middle;

	VideoCapture cap1("nvcamerasrc sensor-id=1 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER); //middle output

	VideoCapture cap2("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER); //output closest to center of board

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
        	cap1 >> fr1;
       		cap2 >> fr2;
		cap3 >> fr3;

		middle = fr2(Range(0, fr2.rows), Range(fr2.cols/3-1, 2*fr2.cols/3-1));
		//apply horizontal concatenation on inputs/matrices
		hconcat(fr1, middle, tile);        	
		hconcat(tile, fr3, out);
        	imshow("Tiled Image", out);

        	if(waitKey(30) >= 0) 
            		break;
    	}
    	return 0;
}
