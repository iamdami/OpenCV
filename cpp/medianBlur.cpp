#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void salt(Mat& image, int n)
{
	int i, j; //임의 위치
	for (int k = 0; k < n; k++) {
		//rand() 는 임의 숫자 생성
		i = rand() % image.cols;
		j = rand() % image.rows; //영상 크기

		if (image.channels() == 1) { //명암도 영상
			image.at<uchar>(j, i) = 255; //salt noise
		}
		else if (image.channels() == 3) { //컬러 영상
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255; //3개 channels
		}
	}
}


int main()
{
	Mat img = imread("../images/lena.jpg");
	Mat gray, res;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	namedWindow("명암영상");
	imshow("명암영상", gray);

	salt(gray, 30000);
	imshow("noised", gray);

	medianBlur(gray, res, 5);
	imshow("res", res);

	waitKey();
	return 0;
}
