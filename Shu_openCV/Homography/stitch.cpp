#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

void FindObj(Mat fr1, Mat fr2){

	if(!fr1.data || !fr2.data)
	{ cout << "--(!) Error reading imgs " << endl; return;}

	int minHessian = 400;
	
	SurfFeatureDetector detector( minHEssian );

	vector<KeyPoint> keypoints1, keypoints2;

	detector.detect( fr1, keypoints1);
	detector.detect( fr2, keypoints2);

	
	SurfDescriptorExtractor extractor;
	
	Mat descriptors1, descriptors2;
	
	extractor.compute( fr1, keypoints1, descriptors1 );
	extractor.compute( fr2, keypoints2, descriptors2 );


	FlannBasedMatcher matcher;
	vector<DMatch> matches;

	matcher.match( descriptors1, descriptors2, matches );

	double max_dist = 0; double min_dist = 100;
	
	for(int i=0; i < descriptors1.rows; i++)
	{
		double dist = matches[i].distance;
		if( dist < min_dist ) min_dist = dist;
		if( dist > max_dist ) max_dist = dist;
	}

	cout << "-- Max dist : " << max_dist << endl;
	cout << "-- Min dist : " << min_dist << endl;

	vector<DMatch> good_matches;

	for(int i=0; i<descriptors1.rows; i++)
	{
		if( matches[i].distance < 3*min_dist )
			good_matches.push_back(matches[i]);
	}

	Mat img_matches;
	drawMatches( fr1, keypoints1, fr2, keypoints2, good_matches, img_matches, 
		     Scalar::all(-1), Scalar::all(-1), vector<char>(), 
		     DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	vector<Point2f> p1;
	vector<Point2f> p2;

	for( int i=0; i<good_matches.size; i++)
	{
		p1.push_back( keypoints1[ good_matches[i].queryIdx ].pt);
		p2.push_back( keypoints2[ good_matches[i].trainIdx ].pt);
	}

	Mat H = findHomography( p1, p2, CV_RANSAC );

	vector<Point2f> obj_corners(4);
	obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint(fr1.cols, 0);
	obj_corners[2] = cvPoint(fr1.cols, fr1.rows);
	obj_corners[3] = cvPoint(0, fr1.rows);
	vector<Point2f> scene_corners(4);

	perspectiveTransform( obj_corners, scene_corners, H );
	

	//-- DRaw lines
	Point2f offset((float) fr1.cols, 0);
	line( img_matches, scene_corners[0] + offset, scene_corners[1] + offset, Scalar(0. 255, 0), 4);
	line( img_matches, scene_corners[1] + offset, scene_corners[2] + offset, Scalar(0. 255, 0), 4);
	line( img_matches, scene_corners[2] + offset, scene_corners[3] + offset, Scalar(0. 255, 0), 4);
	line( img_matches, scene_corners[3] + offset, scene_corners[0] + offset, Scalar(0. 255, 0), 4);
	
	imshow( "Matches & Object detection", img_matches );
	waitKey(0); 

}


int main() {
/*
	VideoCapture cap1("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER);
	

	VideoCapture cap2("nvcamerasrc sensor-id=1 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", CAP_GSTREAMER);

	if(!cap1.isOpened()){
		cout << "Connection cap1 failed" << endl;
		return -1;	
	}

	if(!cap2.isOpened()){
		cout << "Connection cap2 failed" << endl;
		return -1;
	}


	Mat fr1, fr2;
	while(true){
		cap1 >> fr1;
		cap2 >> fr2;	
		FindObj(fr1, fr2);
	}	
	
*/
	Mat fr1, fr2;
	fr1 = imread( "mise.jpg", CV_LOAD_IMAGE_GRAYSCALE );
	fr2 = imread( "mise2.jpg", CV_LOAD_IMAGE_GRAYSCALE );
	FindObj(fr1, fr2);
	
	return 0;
}
