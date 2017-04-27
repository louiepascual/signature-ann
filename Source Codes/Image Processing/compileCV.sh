echo g++ -o `basename $1 .cpp` $1 -I /usr/local/include/opencv -I /usr/local/include/ -L /usr/local/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect
g++ -o `basename $1 .cpp` $1 -I /usr/local/include/opencv -I /usr/local/include/ -L /usr/local/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect
