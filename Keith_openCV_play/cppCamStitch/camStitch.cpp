#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat fr1, fr2, copy1, copy2, pano;
    bool try_use_gpu = false;
    vector<Mat> imgs;
    //VideoCapture cap1(), cap2();

	VideoCapture cap1("nvcamerasrc sensor-id=1 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER); //middle output

	VideoCapture cap2("nvcamerasrc sensor-id=2 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER); //output closest to center of board

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
        	fr1.copyTo(copy1);
        	fr2.copyTo(copy2);

		imgs.push_back(copy1);
		imgs.push_back(copy2);

        	Stitcher test = Stitcher::createDefault(try_use_gpu);
        	Stitcher::Status status = test.stitch(imgs, pano);

        	if (status != Stitcher::OK)
        	{
            		cout << "Error stitching - Code: " <<int(status)<<endl;
            		return -1;
        	}

        	imshow("Frame 1", fr1);
        	imshow("Frame 2", fr2);
        	imshow("Stitched Image", pano);

        	if(waitKey(30) >= 0) 
            		break;
    	}
    	return 0;
}
