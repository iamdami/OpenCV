#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;



int main()
{
	Mat src = imread("../lena.jpg", IMREAD_GRAYSCALE);
	CV_Assert(src.data);

	Mat o1;
	//resize(src, o1, Size(100, 250), 0, 0, INTER_NEAREST);
	resize(src, o1, Size(), 0.5, 1.3, INTER_NEAREST);

	imshow("o1", o1);

	waitKey();
	return 0;

}
