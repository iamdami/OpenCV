#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>   // SIFT & SURF 
using namespace std;
using namespace cv;

int main()
{
	// SURF: Speed Up Robost Features
	// Read input image
	Mat image = imread("../church01.jpg", 0);

	// Construct the SURF feature detector object
	vector < KeyPoint > keypoints;
	Ptr < xfeatures2d::SurfFeatureDetector > ptrSURF = xfeatures2d::SurfFeatureDetector::create(2000.0);

	// detect the keypoints
	ptrSURF->detect(image, keypoints);

	Mat featureImage;
	drawKeypoints(image, keypoints, featureImage, Scalar(255, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// Display the keypoints
	namedWindow("SURF");
	moveWindow("SURF", 250, 250);
	imshow("SURF", featureImage);

	cout << "Number of SURF keypoints: " << keypoints.size() << endl;

	// Read a second input image
	image = imread("../church02.jpg", IMREAD_GRAYSCALE);

	keypoints.clear();
	// Detect the SURF features
	ptrSURF->detect(image, keypoints);

	drawKeypoints(image, keypoints, featureImage, Scalar(255, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// Display the keypoints
	namedWindow("SURF2");
	moveWindow("SURF2", 500, 250);
	imshow("SURF2", featureImage);


	// SIFT: Scale Invariant Feature Transform
	// Read input image
	image = imread("../church01.jpg", IMREAD_GRAYSCALE);

	keypoints.clear();
	// Construct the SIFT feature detector object
	Ptr< xfeatures2d::SiftFeatureDetector > ptrSIFT = xfeatures2d::SiftFeatureDetector::create();
	// detect the keypoints
	ptrSIFT->detect(image, keypoints);

	drawKeypoints(image, keypoints, featureImage, Scalar(255, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// Display the keypoints
	namedWindow("SIFT");
	moveWindow("SIFT", 750, 250);
	imshow("SIFT", featureImage);

	cout << "Number of SIFT keypoints: " << keypoints.size() << std::endl;
	waitKey();
	return 0;
}
