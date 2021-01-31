#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("../images/lena.jpg", IMREAD_COLOR);

	imshow("image", image);
	waitKey();
	return 0;
}
