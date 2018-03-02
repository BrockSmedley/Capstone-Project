//#include <opencv2/core/core.h>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <string.h>

using namespace std;
using namespace cv;

int main (int argc, char** argv){

	if(argc != 2)
	{
		cout << "Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}

	Mat image;
	image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	if(!image.data)
	{
		cout << "Could not find or open image." << endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);

	waitKey(0);
	return 0;

}
