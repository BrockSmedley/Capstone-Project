#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
	
	Mat image;
	image = imread("Keith.jpg", CV_LOAD_IMAGE_COLOR);
	
	if( ! image.data )
	{
		cout << "Could not open the image" << endl;
		return -1;
	}

	namedWindow( "Display window" , WINDOW_NORMAL );
	imshow( "Display window" , image );

	waitKey(0);

	return 0;
}
