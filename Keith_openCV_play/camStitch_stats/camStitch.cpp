#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;
using namespace cv;

Stitcher::Mode mode = Stitcher::PANORAMA;

int streaming(VideoCapture cap1, VideoCapture cap2, double start)
{
    Mat fr1, fr2, copy1, copy2, pano;
    bool try_use_gpu = false;
    vector<Mat> imgs;

        cap1 >> fr1;
       	cap2 >> fr2;

//       	fr1.copyTo(copy1);
//       	fr2.copyTo(copy2);
			
	imgs.push_back(fr1);
	imgs.push_back(fr2);
        Ptr<Stitcher> test = Stitcher::create(mode, try_use_gpu);
	//test.stitch(imgs, pano);
       	Stitcher::Status status = test->stitch(imgs, pano);

//	Mat faster;
//	test.composePanorama(imgs, faster);
  
     	if (status != Stitcher::OK)
       	{
        	cout << "Error stitching - Code: " <<int(status)<<endl;
            	return -1;
       	}
//      namedWindow( "Stitched Image", WINDOW_NORMAL);
//	imshow("Frame 1", fr1);
//     	imshow("Frame 2", fr2);
	
	cout << "start: " << double(start) << " seconds " << endl;

	time_t end;
	time(&end);

	cout << "end: " << double(end) << " seconds " << endl;
	double seconds = difftime (end, start);
	cout << "time taken: " << seconds << " seconds " << endl;

     	imshow("Stitched Image", pano);
//	imshow("Compose Image", faster);

	//waitKey(0);
	if(waitKey(1) >= 0) 
       		return -1;
}

int main(int argc, char *argv[])
{
    Mat fr1, fr2, copy1, copy2, pano;
    bool try_use_gpu = false;
    vector<Mat> imgs;
    //VideoCapture cap1(), cap2();

	VideoCapture cap1("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER); //middle output

	VideoCapture cap2("nvcamerasrc sensor-id=2 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER); //output closest to center of board

	if(!cap1.isOpened()){
		cout << "connection cap1 failed" << endl;
		return -1;
	}

	if(!cap2.isOpened()){
		cout << "connection cap2 failed" << endl;
		return -1;
	}

	double fps1 = cap1.get(CV_CAP_PROP_FPS);
	double fps2 = cap2.get(CV_CAP_PROP_FPS);
	
	cout << "frames/sec, cap1: " << fps1 << " frames/sec, cap2: " << fps2 << endl;

	//time_t start;
	//time(&start);		


	while(true)
	{
		time_t start;
		int test = 0;

		time(&start);
		test = streaming(cap1, cap2, start);
		//cout << "test: " << int(test) << endl;
   	}

    	return 0;
}
