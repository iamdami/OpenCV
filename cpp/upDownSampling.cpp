#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;



int main()
{
	Mat src = imread("../lena.jpg", IMREAD_GRAYSCALE);
	CV_Assert(src.data);

	Mat down, up;
	pyrDown(src, down, Size());
	pyrUp(src, up, Size());


	imshow("down", down);
	imshow("up", up);


	waitKey();
	return 0;
}
