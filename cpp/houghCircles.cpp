#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void hough_circles()
{
	Mat src = imread("../images/coins.png", IMREAD_GRAYSCALE); //파일 가져와 그레이 스케일
	if (src.empty()) {
		cerr << "Image Load Failed!" << endl;
		return;
	}
	//Mat blurred;
	//blur(src, blurred, Size(5, 5)); // 5X5 크기의 블러링 수행

	vector<Vec3f> circles; //float로 3개 값 (x,y)좌표와 반지름. 총 3개 필요
	HoughCircles(src, circles, HOUGH_GRADIENT, 1, 50, 150, 30);
	//Hough 변환 이용해 그레이스케일 이미지에서 Circle 찾는 함수

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (Vec3f cir : circles) {
		Point center(cvRound(cir[0]), cvRound(cir[1]));
		int radius = cvRound(cir[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA); //빨간색, 라인 굵기 2
	}
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}


int main()
{
	hough_circles();

	return 0;
}
