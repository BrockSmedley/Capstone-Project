DISPLAY=:0 gst-launch-1.0 nvcamerasrc sensor-id=0 fpsRange="30 30" ! 'video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, \
framerate=(fraction)2/1' ! nvegltransform ! nveglglessink  nvcamerasrc sensor-id=2 fpsRange="30 30" ! 'video/x-raw(memory:NVMM), width=(int)640, \
height=(int)480, format=(string)I420, framerate=(fraction)60/1' ! nvegltransform ! nveglglessink nvcamerasrc sensor-id=1 fpsRange="30 30" ! 'video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)24/12' ! nvegltransform ! nveglglessink -e
