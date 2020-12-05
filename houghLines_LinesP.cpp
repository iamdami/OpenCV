#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void hough_lines()
{
	Mat src = imread("../images/building.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image Load Failed!" << endl;
		return;
	}
	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec2f> lines; //Vec2f  float 타입의 두 개가 쌍으로 됨
	HoughLines(edge, lines, 1, CV_PI / 180, 250); //후프 라인의 결과가 lines에 들어감
	// 세번째값 기본값, 그 다음 로우, 세타
	// 기준을 라디안값 사용
	

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (size_t i = 0; i < lines.size(); i++) {
		float r = lines[i][0], t = lines[i][1]; //첫번째값 로우, 두번째값 세타
		double cos_t = cos(t), sin_t = sin(t);
		double x0 = r * cos_t, y0 = r * sin_t;
		double alpha = 1000;

		Point pt1(cvRound(x0 - alpha * (sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 + alpha * (sin_t)), cvRound(y0 - alpha * cos_t));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA); // 빨간색, 라인 굵기 2
	}
	cout << "# of lines with a threshold of 250 = " << lines.size() << endl;
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}


void hough_line_segments()
{
	Mat src = imread("../images/building.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image Load Failed!" << endl;
		return;
	}
	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec4i> lines; //int 타입으로 4개
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 150, 10);
	//단계 크기 1, PI/180,  minLength=150, maxGap =10, minVote=160

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

int main()
{
	hough_lines();
	hough_line_segments();
	return 0;
}
