
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

void main()
{
    Mat srcImg = imread("../images/banana.jpg");
    imshow("src", srcImg);
    Mat dstImg(srcImg.size(), CV_8UC3, Scalar::all(0));

    cvtColor(srcImg, srcImg, COLOR_BGR2GRAY);
    threshold(srcImg, srcImg, 200, 255, THRESH_BINARY_INV);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarcy;
    findContours(srcImg, contours, hierarcy, 0, CHAIN_APPROX_NONE);

    vector<vector<Point>> contours_poly(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        approxPolyDP(Mat(contours[i]), contours_poly[i], 15, true);

        drawContours(dstImg, contours_poly, i, Scalar(0, 0, 255), 2, 8);
    }
    imshow("approx", dstImg);
    waitKey(0);
}
