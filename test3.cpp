#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("../images/humming_bird.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Mat dst(image.size(), image.type());

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			dst.at<uchar>(i, j) = 255-image.at<uchar>(i, j);
		}

	}

	imshow("image", image);
	imshow("dst", dst);

	waitKey();
	return 0;
}
