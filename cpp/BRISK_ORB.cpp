#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	// BRISK: Binary Robust Invariant Scalable Keypoints
	// Read input image
	Mat image = imread("../images/church01.jpg", IMREAD_GRAYSCALE);
	Mat featureImage;
	// Construct another BRISK feature detector object
	vector < KeyPoint > keypoints;
	Ptr < BRISK > ptrBRISK = BRISK::create(60, 5);  // 60: threshold for BRISK points to be accepted, 5: number of octaves

													// Detect the BRISK features
	ptrBRISK->detect(image, keypoints);

	drawKeypoints(image, keypoints, featureImage, cv::Scalar(255, 255, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// Display the keypoints
	namedWindow("BRISK");
	moveWindow("BRISK", 300, 250);
	imshow("BRISK", featureImage);

	cout << "Number of BRISK keypoints: " << keypoints.size() << endl;

	// ORB: ORiented BRIEF
	// Read input image
	image = imread("../images/church01.jpg", IMREAD_GRAYSCALE);

	keypoints.clear();

	// Construct the BRISK feature detector object
	Ptr< ORB > ptrORB = ORB::create(75, 1.2, 8);  // 75: total number of keypoints, 1.2 : scale factor between layers, 8 : number of layers in pyramid

												  // detect the keypoints
	ptrORB->detect(image, keypoints);

	drawKeypoints(image, keypoints, featureImage, Scalar(255, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// Display the keypoints
	namedWindow("ORB");
	moveWindow("ORB", 500, 250);
	imshow("ORB", featureImage);

	cout << "Number of ORB keypoints: " << keypoints.size() << endl;
	waitKey();
	return 0;
}
