#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void corner_harris()
{
	Mat src = imread("../images/building.jpg", IMREAD_GRAYSCALE); //그레이스케일로 읽어오기
	if (src.empty()) { //예외처리
		cerr << "Image Load Failed!" << endl;
		return;
	}
	Mat harris, harris_norm; //결과값 넣어주기 위한 Mat
	//openCV 제공 함수 cornerHarris()
	cornerHarris(src, harris, 3, 3, 0.04); 
	normalize(harris, harris_norm, 0, 255, NORM_MINMAX, CV_8U); //정규화해주는 함수

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR); //그레이레벨한 것을 다시 컬러로 변환

	// non-maximum suppression
	for (int j = 1; j < harris.rows - 1; j++) { //주변 4개 방향보다 특징점 값이 더 커야 함
		for (int i = 1; i < harris.cols - 1; i++) {
			if (harris_norm.at<uchar>(j, i) > 120) { //120은 임의로 정해준 값
				if (harris.at<float>(j, i) > harris.at<float>(j - 1, i) &&
					harris.at<float>(j, i) > harris.at<float>(j + 1, i) &&
					harris.at<float>(j, i) > harris.at<float>(j, i - 1) &&
					harris.at<float>(j, i) > harris.at<float>(j, i + 1)) {
					circle(dst, Point(i, j), 5, Scalar(0, 0, 255), 2); //빨강 원, 굵기 2
				}
			}
		}
	}
	imshow("src", src);
	imshow("harris_norm", harris_norm);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void corner_fast()
{
	Mat src = imread("../images/building.jpg", IMREAD_GRAYSCALE); //그레이 스케일로 읽어오기
	if (src.empty()) { //예외처리
		cerr << "Image Load Failed!" << endl;
		return;
	}

	vector<KeyPoint> keypoints; //특징점 나타내는 것
	//Features from Accelerated Segment Test, 2006
	FAST(src, keypoints, 60, true); // th: 60, non-maximum supression : true

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);
	for (KeyPoint kp : keypoints) {
		Point pt(cvRound(kp.pt.x), cvRound(kp.pt.y)); //pt는 포인터
		circle(dst, pt, 5, Scalar(0, 0, 255), 2); //빨강색, 두께 2
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main()
{
	corner_harris();

	corner_fast();

	return 0;
}
