#!/usr/bin/env python

from __future__ import print_function
import stitcher
#from imutils.video import VideoStream

import numpy as np
import datetime
#import imutils
import time
import cv2
import sys

print("[INFO] starting cameras...")
leftStream = cv2.VideoCapture("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink")
rightStream = cv2.VideoCapture("nvcamerasrc sensor-id=2 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink")
time.sleep(2.0)

stitcher = cv2.createStitcher(False)
total = 0

while True:
	left_img, left_ok = leftStream.read()
	right_img, right_ok = rightStream.read()

	if left_ok is None:
		print("left camera failed")
		break

	if right_ok is None:
		print("right camera failed")
		break

	status, result = stitcher.stitch([left_img, right_img])

	if result is None:
		print("[INFO] homography could not be computed")
		break

	total += 1
	timeStamp = datetime.datetime.now()
	ts = timestamp.strftime("%A %d %B %Y %I:%M:%S%p")
	cv2.putText(result, ts, (10, result.shape[0] - 10),
		cv2.FONT_HERSHEY_SIMPLEX, 0.35, (0, 0, 255), 1)

	cv2.imshow("result", result)
	cv2.imshow("left frame", left)
	cv2.imshow("right frame", right)
	key = cv2.waitKey(1) & 0xFF

	if key == ord("q"):
		break

print("[INFO] cleaning up...")
cv2.destroyAllWindows()
leftStream.stop()
rightStream.stop()


