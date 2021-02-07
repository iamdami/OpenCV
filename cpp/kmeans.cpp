#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat samples(50, 2, CV_32F);

	for (int y = 0; y < samples.rows; y++) {
		samples.at<float>(y, 0) = (rand() % 255);
		samples.at<float>(y, 1) = (rand() % 255);
	}
	Mat dst(256, 256, CV_8UC3);

	for (int y = 0; y < samples.rows; y++) {
		float x1 = samples.at<float>(y, 0);
		float x2 = samples.at<float>(y, 1);
		circle(dst, Point(x1, x2), 3, Scalar(255, 0, 0));
	}
	imshow("dst", dst);

	Mat result;
	Mat labels(50, 1, CV_8UC1);
	Mat centers;
	result = Mat::zeros(Size(256, 256), CV_8UC3);
	kmeans(samples, 2, labels, TermCriteria(TermCriteria::MAX_ITER | TermCriteria::EPS, 10000, 0.0001), 3, KMEANS_PP_CENTERS, centers);

	for (int y = 0; y < samples.rows; y++) {
		float x1 = samples.at<float>(y, 0);
		float x2 = samples.at<float>(y, 1);
		int cluster_idx = labels.at<int>(y, 0);
		if (cluster_idx == 0)
			circle(result, Point(x1, x2), 3, Scalar(255, 0, 0));
		else
			circle(result, Point(x1, x2), 3, Scalar(0, 0, 255));
	}
	imshow("result", result);

	waitKey();
	return 0;
}
