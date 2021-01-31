#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat ref_src, ref_gray;
	ref_src = imread("../images/banana.jpg");
	cvtColor(ref_src, ref_gray, COLOR_BGR2GRAY);//그레이레벨로 변환
	threshold(ref_gray, ref_src, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);//오츄이진화


	// 외곽선 검출
	vector < vector<Point> > contours;
	findContours(ref_src, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);


	Mat dst(ref_src.size(), CV_8U, Scalar(255));
	for (int i = 0; i < contours.size(); i++) {
		drawContours(dst, contours, i, Scalar(0), 2);
		//외곽선 그리기
	}

	// boundingRect (red)
	Rect rt = boundingRect(contours[0]);
	// draw the rectangle
	rectangle(dst, rt, Scalar(0, 0, 255), 2);


	// enclosing circle (blue)
	float radius;
	Point2f center;
	minEnclosingCircle(contours[1], center, radius);
	circle(dst, center, radius, Scalar(255, 0, 0), 2);


	imshow("ref_src", dst);

	waitKey();
	return 0;
}
