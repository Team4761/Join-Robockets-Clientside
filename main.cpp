#include <iostream>
#include <opencv2/opencv.hpp>

#include "clicker.hpp"

using namespace cv;
using namespace std;

string window_title = "Join-Robockets Clientside Software";

int main() {
    //Initialize camera.
    VideoCapture cap(CV_CAP_ANY);
    if(!cap.isOpened()) {
        cerr << "Could not open image capture device!" << endl;
        exit(EXIT_FAILURE);
    }

    Mat frame;
    namedWindow(window_title);
    while(1) {
        //Capture and show image.
        cap >> frame;
        imshow(window_title, frame);

        //Quit if any key has been pressed.
        if(waitKey(30) >= 0) {
            break;
        }
    }
    //VideoCapture is closed automatically.
    return 0;
}