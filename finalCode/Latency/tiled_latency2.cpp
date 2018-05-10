#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat fr1, fr2, fr3, tile, middle;

	VideoCapture cap1("nvcamerasrc sensor-id=1 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER); //middle output

	VideoCapture cap2("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER); //output closest to center of board

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
		timespec begin, end;
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);

        	cap1 >> fr1;
       		cap2 >> fr2;

		middle = fr2(Range(0, fr2.rows), Range(fr2.cols/3-1, 2*fr2.cols/3-1));
		//apply horizontal concatenation on inputs/matrices
		hconcat(fr1, middle, tile);        	
		
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
                putText(tile, format("Latency = %f sec",(long long) (end.tv_sec-begin.tv_sec) + (end.tv_nsec-begin.tv_nsec)/1e9), Point(30, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,0,255));

        	imshow("Tiled Image", tile);
		waitKey(1);
    	}

    	return 0;
}
