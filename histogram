#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max = 256)
{
	int histSize[] = { bins };//히스토그램 계급 개수
	float range[] = { 0, (float)range_max }; // 채널 화소값 범위
	int channels[] = { 0 }; //채널 목록
	const float* ranges[] = { range };

	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
}

void draw_histo(Mat hist, Mat& hist_img, Size size = Size(256, 200))
{
	hist_img = Mat(size, CV_8U, Scalar(255));
	float bin = (float)hist_img.cols / hist.rows;
	normalize(hist, hist, 0, size.height, NORM_MINMAX);

	for (int i = 0; i < hist.rows; i++)
	{
		float start_x = (i * bin);
		float end_x = (i + 1) * bin;
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at <float>(i));

		if (pt2.y > 0)
			rectangle(hist_img, pt1, pt2, Scalar(0), -1);
	}
	flip(hist_img, hist_img, 0);
}

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

	Mat hist, hist_img, eq_img;
	calc_Histo(gray, hist, 256);
	cout << hist.t() << endl;
	//histogram(openCV)

	draw_histo(hist, hist_img);
	imshow("hist_img1", hist_img);
	//draw histogram

	imshow("image", image);
	imshow("gray", gray);
	waitKey();
	return 0;
}
