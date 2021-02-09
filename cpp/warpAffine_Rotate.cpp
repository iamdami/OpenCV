#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

// Change image position

int main()
{
	Mat src = imread("../images/lena.jpg", IMREAD_GRAYSCALE);
	CV_Assert(src.data);

	Mat dst;
	Size dsize = Size(src.cols * 2, src.rows * 2);
	Point center = Point(src.cols / 2.0, src.rows / 2.0);

	Mat M = getRotationMatrix2D(center, 135, 1.0);
	warpAffine(src, dst, M, dsize, INTER_LINEAR);

	imshow("Rotated", dst);


	waitKey();
	return 0;
}
