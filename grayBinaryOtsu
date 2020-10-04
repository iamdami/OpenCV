#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat image2 = imread("../images/hillary_clinton.jpg");

	imshow("image2", image2);

	Mat gray, binary, otsu;
	cvtColor(image2, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 128, 255, THRESH_BINARY);

	int value = threshold(gray, otsu, 0, 255, THRESH_OTSU);
	cout << "Otsu's threshold: " << value << endl;

	imshow("gray", gray);
	imshow("binary", binary);
	imshow("ostu", otsu);

	waitKey();
	return 0;
}
