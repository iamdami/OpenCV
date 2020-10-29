#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void sobel_derivative()
{
	Mat src = imread("../lena.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat mx = Mat_<float>({ 1, 3 }, { -1 / 2.f, 0, 1 / 2.f });
	Mat my = Mat_<float>({ 3, 1 }, { -1 / 2.f, 0, 1 / 2.f });

	cout << "mx = " << mx << endl;
	cout << "my = " << my << endl;

	// 
	float my1[] = { -1, -2, -1,
		0,  0,  0,
		1,  2,  1 };

	Mat dx, dy, dy1;
	Mat my1_filter(3, 3, CV_32F, my1);
	filter2D(src, dx, -1, mx, Point(-1, -1), 0);
	filter2D(src, dy, -1, my, Point(-1, -1), 128);
	filter2D(src, dy1, CV_32F, my1_filter, Point(-1, -1));
	dy1.convertTo(dy1, CV_8U);

	imshow("src", src);
	imshow("dx", dx); imshow("dy", dy); 
	imshow("dy1", dy1);

	waitKey();
	destroyAllWindows();
}

void sobel_edge()
{
	Mat src = imread("../lena.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

	Mat fmag, mag;
	magnitude(dx, dy, fmag);
	fmag.convertTo(mag, CV_8UC1);

	Mat edge = mag > 150;

	imshow("src", src);
	imshow("mag", mag);
	imshow("edge", edge);

	waitKey();
	destroyAllWindows();
}

void canny_edge()
{
	Mat src = imread("../lena.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	Mat dst1, dst2;
	Canny(src, dst1, 50, 100);
	Canny(src, dst2, 50, 150);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}

void laplacian_edge()
{
	Mat src, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_32F;	// CV_16S
	src = imread("../lena.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	Mat abs_dst;
	Laplacian(src, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);

	imshow("Image", src);
	imshow("Laplacian", abs_dst);
	waitKey(0);
	destroyAllWindows();
}

int main()
{
	sobel_derivative();
	sobel_edge();
	laplacian_edge();
	canny_edge();

	return 0;
}
