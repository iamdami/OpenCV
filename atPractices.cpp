#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("../images/lena.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Mat dst(image.size(), image.type());


	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			dst.at<uchar>(i, j) = image.at<uchar>(i, j) + 100;
//			dst.at<uchar>(i, j) = saturate_cast<uchar>(image.at<uchar>(i, j) + 100);
			//saturate_cast는 uchar가 가질 수 있는 최대값까지 잘라줌(255)
//			dst.at<uchar>(i, j) = 255 - image.at<uchar>(i, j); //색 반전
		}
	}
	imshow("image", image);
	imshow("dst", dst);

	waitKey();
	return 0;
}
