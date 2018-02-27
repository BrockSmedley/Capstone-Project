gst-launch-1.0 nvcamerasrc sensor-id=0 ! videoscale ! videoconvert ! video/x-raw-yuv, width=420, height=480 ! videobox border-alpha=0 left=-640 ! videomixer name=mix ! videoconvert ! xvimagesink nvcamerasrc sensor-id=2 ! videoscale ! videoconvert ! video/x-raw-yuv, width=640, height=480 ! videobox right=-640 ! mix.

