#include <iostream>
#include <opencv2/opencv.hpp>

#include "clicker.hpp"

using namespace cv;
using namespace std;

string window_title = "Join-Robockets Clientside Software";
int h_lower = 0, s_lower = 0, v_lower = 0;
int h_upper = 180, s_upper = 255, v_upper = 255;

int main() {
    //Initialize camera.
    VideoCapture cap(CV_CAP_ANY);
    if(!cap.isOpened()) {
        cerr << "Could not open image capture device!" << endl;
        exit(EXIT_FAILURE);
    }

    Mat frame, hsv, filtered;
    namedWindow(window_title);
    createTrackbar("Hue Lower", window_title, &h_lower, 180, NULL);
    createTrackbar("Hue Upper", window_title, &h_upper, 180, NULL);
    createTrackbar("Saturation Lower", window_title, &s_lower, 255, NULL);
    createTrackbar("Saturation Upper", window_title, &s_upper, 255, NULL);
    createTrackbar("Value Lower", window_title, &v_lower, 255, NULL);
    createTrackbar("Value Upper", window_title, &v_upper, 255, NULL);

    while(1) {
        //Capture and show image.
        cap >> frame;
        cvtColor(frame, hsv, CV_BGR2HSV);
        inRange(hsv, Scalar(h_lower, s_lower, v_lower), Scalar(h_upper, s_upper, v_upper), filtered);
        imshow(window_title, filtered);

        //Quit if any key has been pressed.
        if(waitKey(30) >= 0) {
            break;
        }
    }
    //VideoCapture is closed automatically.
    return 0;
}