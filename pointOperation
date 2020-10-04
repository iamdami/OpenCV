#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("../images/hillary_clinton.jpg", IMREAD_COLOR);

	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);

	imshow("output1", gray + 30);
	imshow("output2", gray - 30);
	imshow("output3", gray * 1.3);
	imshow("output4", gray / 1.3);
	imshow("output5", 255 - gray);

	waitKey();
	return 0;
}
