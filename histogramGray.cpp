#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("../images/lena.jpg", IMREAD_COLOR);
	CV_Assert(image.data);
	Mat roi, gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	Rect rt = Rect(10, 10, 5, 5);
	roi = gray(rt);
	cout << "roi=" << roi << endl;
	int histogram[256] = { 0 };
	for (int y = 0; y < gray.rows; y++)
		for (int x = 0; x < gray.cols; x++)
			histogram[(int)gray.at<uchar>(y, x)]++;

	for (int count : histogram)
		cout << count << ",";
	cout << endl;

	imshow("image", image);
	imshow("gray", gray);
	waitKey();
	return 0;
}
