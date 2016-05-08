#include <iostream>
#include <opencv2/opencv.hpp>

#include "clicker.hpp"

using namespace cv;
using namespace std;

string window_title = "Join-Robockets Clientside Software";

//HSV filter variables
int h_lower = 0, s_lower = 0, v_lower = 0;
int h_upper = 180, s_upper = 255, v_upper = 255;
Scalar hsv_lower(h_lower, s_lower, v_lower);
Scalar hsv_upper(h_upper, s_upper, v_upper);

//Camera settings
int exposure = 50;
VideoCapture cap(CV_CAP_ANY);

/*
 * Callback for exposure trackbar. Sets camera exposure.
 */
void exposure_callback(int, void*) {
    cap.set(CV_CAP_PROP_EXPOSURE, exposure);
}

/*
 * Callback for the HSV trackbars. Update the hsv_upper and hsv_lower scalars
 * with new values.
 */
void filter_callback(int, void*) {
    hsv_lower = Scalar(h_lower, s_lower, v_lower);
    hsv_upper = Scalar(h_upper, s_upper, v_upper);
}

int main() {
    //Check if camera works
    if(!cap.isOpened()) {
        cerr << "Could not open image capture device!" << endl;
        exit(EXIT_FAILURE);
    }

    Mat frame, hsv, filtered;
    namedWindow(window_title);
    createTrackbar("H Lower", window_title, &h_lower, 180, filter_callback);
    createTrackbar("H Upper", window_title, &h_upper, 180, filter_callback);
    createTrackbar("S Lower", window_title, &s_lower, 255, filter_callback);
    createTrackbar("S Upper", window_title, &s_upper, 255, filter_callback);
    createTrackbar("V Lower", window_title, &v_lower, 255, filter_callback);
    createTrackbar("V Upper", window_title, &v_upper, 255, filter_callback);
    createTrackbar("Exposure", window_title, &exposure, 255, exposure_callback);

    while(1) {
        //Capture and show image.
        cap >> frame;
        cvtColor(frame, hsv, CV_BGR2HSV);
        inRange(hsv, hsv_lower, hsv_upper, filtered);
        imshow(window_title, filtered);

        //Quit if any key has been pressed.
        if(waitKey(30) >= 0) {
            break;
        }
    }
    //VideoCapture is closed automatically.
    return 0;
}