#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	// Grid adaptor detection
	Mat image = imread("../images/church01.jpg", 0);
	if (!image.data)
		return 0;

	int total(100); // requested number of keypoints
	int hstep(5), vstep(3); // a grid of 5 columns by 3 rows
							// hstep= vstep= 1; // try without grid
	int hsize(image.cols / hstep), vsize(image.rows / vstep);
	int subtotal(total / (hstep*vstep)); // number of keypoints per grid
	Mat imageROI;
	vector< KeyPoint > gridpoints;
	vector < KeyPoint > keypoints;

	cout << "Grid of " << vstep << " by " << hstep << " each of size " << vsize << " by " << hsize << endl;

	// detection with low threshold
	Ptr < FastFeatureDetector > ptrFAST = FastFeatureDetector::create();
	ptrFAST->setThreshold(20);
	// non-max suppression
	ptrFAST->setNonmaxSuppression(true);

	// The final vector of keypoints
	// detect on each grid
	for (int i = 0; i < vstep; i++)
		for (int j = 0; j < hstep; j++) {

			// create ROI over current grid
			imageROI = image(Rect(j*hsize, i*vsize, hsize, vsize));
			// detect the keypoints in grid
			gridpoints.clear();
			ptrFAST->detect(imageROI, gridpoints);
			cout << "Number of FAST in grid " << i << "," << j << ": " << gridpoints.size() << endl;
			if (gridpoints.size() > subtotal) {
				for (auto it = gridpoints.begin(); it != gridpoints.begin() + subtotal; ++it) {
					cout << "  " << it->response << endl;
				}
			}

			// get the strongest FAST features
			auto itEnd(gridpoints.end());
			if (gridpoints.size() > subtotal) { // select the strongest features
				nth_element(gridpoints.begin(), gridpoints.begin() + subtotal, gridpoints.end(),
					[](KeyPoint& a, KeyPoint& b) {return a.response > b.response; });
				itEnd = gridpoints.begin() + subtotal;
			}

			// add them to the global keypoint vector
			for (auto it = gridpoints.begin(); it != itEnd; ++it) {
				it->pt += Point2f(j*hsize, i*vsize); // convert to image coordinates
				keypoints.push_back(*it);
				std::cout << "  " << it->response << std::endl;
			}
		}

	// draw the keypoints
	cv::drawKeypoints(image, keypoints, image, cv::Scalar(255, 255, 255), cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);

	// Display the keypoints
	namedWindow("FAST Features (grid)");
	moveWindow("FAST Features (grid)", 500, 250);
	imshow("FAST Features (grid)", image);

	waitKey();
	return 0;
}
