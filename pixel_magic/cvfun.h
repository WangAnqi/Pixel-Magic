#pragma once
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <iostream>
#include <cmath>
using namespace cv;
using namespace std;
Mat angleRotate(Mat& src, double angle);
Mat horizon_reverse(Mat &src);
Mat vertical_reverse(Mat &src);
Mat round_clip(Mat &src, Rect rect);