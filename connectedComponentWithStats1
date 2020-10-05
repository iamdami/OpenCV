#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat img = Mat(400, 500, CV_8U, Scalar(0));
	circle(img, Point(100, 100), 50, Scalar(255), -1);
	rectangle(img, Rect(300, 300, 50, 40), Scalar(255), -1);
	imshow("img", img);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(img, labels, stats, centroids);
	cout << "Stats:\n " << stats << endl;
	cout << "centroids:\n " << centroids << endl;
	cout << "number of labels: " << cnt << endl;

	waitKey();
	return 0;
}
