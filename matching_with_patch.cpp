#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>   // SIFT & SURF 
using namespace std;
using namespace cv;

void matching_with_patch()
{
	// image matching
	// Read input image
	Mat image1 = imread("../images/church01.jpg", IMREAD_GRAYSCALE);
	Mat image2 = imread("../images/church02.jpg", IMREAD_GRAYSCALE);
	imshow("image1", image1); imshow("image2", image2);

	// define keypoints vector
	vector < KeyPoint > keypoints1;
	vector < KeyPoint > keypoints2;

	// define feature detector
	Ptr < FeatureDetector > ptrDetector; // generic detector
	ptrDetector = FastFeatureDetector::create(80); // selecting the FAST detector

												   // keypoints detection
	ptrDetector->detect(image1, keypoints1);
	ptrDetector->detect(image2, keypoints2);
	cout << "# of keypoints (image1) : " << keypoints1.size() << endl;
	cout << "# of keypoints (image2) : " << keypoints2.size() << endl;

	// define a square neighborhood
	const int nsize(11); // size of neighborhood
	Rect neighborhood(0, 0, nsize, nsize); // 11 x 11
	Mat patch1, patch2;

	// All keypoints in first image find best match in second image
	Mat result;
	vector < DMatch > matches;

	// for all keypoints1 in image1
	for (int i = 0; i < keypoints1.size(); i++) {
		// define image patch
		neighborhood.x = keypoints1[i].pt.x - nsize / 2;
		neighborhood.y = keypoints1[i].pt.y - nsize / 2;

		// if neighborhood of points outside image, then continue with next points
		if (neighborhood.x < 0 || neighborhood.y < 0 || neighborhood.x + nsize >= image1.cols || neighborhood.y + nsize >= image1.rows)
			continue;

		// patch in image1
		patch1 = image1(neighborhood);
		// reset best correlation value
		DMatch bestMatch;

		// for all keypoints in image2
		for (int j = 0; j < keypoints2.size(); j++) {
			neighborhood.x = keypoints2[j].pt.x - nsize / 2; // define image patch
			neighborhood.y = keypoints2[j].pt.y - nsize / 2;
			if (neighborhood.x < 0 || neighborhood.y < 0 || neighborhood.x + nsize >= image2.cols || neighborhood.y + nsize >= image2.rows)
				continue;
			patch2 = image2(neighborhood); // patch in image2

										   // match the two patches
			matchTemplate(patch1, patch2, result, TM_SQDIFF);

			// check if it is a best match
			if (result.at<float>(0, 0) < bestMatch.distance) {
				bestMatch.distance = result.at<float>(0, 0);
				bestMatch.queryIdx = i;
				bestMatch.trainIdx = j;
			}
		}
		// add the best match to vector
		matches.push_back(bestMatch);
	}

	cout << "Number of matches : " << matches.size() << endl;

	// extract the 25 best matches
	nth_element(matches.begin(), matches.begin() + 25, matches.end());
	matches.erase(matches.begin() + 25, matches.end());

	cout << "NUMBER of MATCHES (AFTER): " << matches.size() << endl;

	// Draw the matching results
	Mat matchImage;
	drawMatches(image1, keypoints1, image2, keypoints2, matches, matchImage, Scalar(255, 255, 255), Scalar(0, 0, 255));

	namedWindow("Matches");
	imshow("Matches", matchImage);

//
	waitKey();
}

int main()
{
	matching_with_patch();

	return 0;
}
