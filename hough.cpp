#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void hough_lines()
{
	Mat src = imread("PutFileName.jpg", IMREAD_GRAYSCALE); 
	if (src.empty()) {
		cerr << "Image Load Failed!" << endl;
		return;
	}
	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec2f> lines; //Vec2f  float 타입의 두 개가 쌍으로 됨
	HoughLines(edge, lines, 1, CV_PI / 180, 250); //후프 라인의 결과가 lines에 들어감
	// 세번째 있는게 기본값, 그 다음이 로우, 세타
	// 기준을 라디안값 사용

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (size_t i = 0; i < lines.size(); i++) {
		float r = lines[i][0], t = lines[i][1]; //첫번째값은 로우, 두번째값은 세타
		double cos_t = cos(t), sin_t = sin(t);
		double x0 = r * cos_t, y0 = r * sin_t;
		double alpha = 1000;

		Point pt1(cvRound(x0 - alpha * (sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 + alpha * (sin_t)), cvRound(y0 - alpha * cos_t));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA); // 빨간색으로 라인 굵기 2
	}
	cout << "# of lines = " << lines.size() << endl;
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void hough_line_segments()
{
	Mat src = imread("../building.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image Load Failed!" << endl;
		return;
	}
	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec4i> lines; //int 타입으로 4개
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (Vec4i li : lines) {
		line(dst, Point(li[0], li[1]), Point(li[2], li[3]), Scalar(0, 0, 255), 2, LINE_AA);
	}
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}


void hough_circles()
{
	Mat src = imread("../coins.png", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image Load Failed!" << endl;
		return;
	}
	Mat blurred;
	blur(src, blurred, Size(3, 3));

	vector<Vec3f> circles; //float로 3개 값 (x,y)좌표와 반지름. 총 3개 필요
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (Vec3f cir : circles) {
		Point center(cvRound(cir[0]), cvRound(cir[1]));
		int radius = cvRound(cir[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main()
{
	hough_lines();
	hough_line_segments();
	hough_circles();

	return 0;
}
