#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;



int main()
{
	Mat src = imread("../lena.jpg", IMREAD_GRAYSCALE);
	CV_Assert(src.data);

	Rect rect(250, 250, 100, 100); //x, y, 가로, 세로
	Mat roi = src(rect);//이미지에 rect값 적용
	Mat o1;

	resize(roi, o1, Size(), 4.0, 4.0, INTER_NEAREST);
	//roi를 해당 사이즈로 변환


	imshow("Inter_Nearest", o1);


	waitKey();
	return 0;
}
