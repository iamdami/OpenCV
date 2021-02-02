#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	// Read input binary image
	Mat src = imread("../images/binaryGroup.bmp", IMREAD_GRAYSCALE);
	namedWindow("Binary Image");
	imshow("Binary Image", src);

	// Get the contours of the connected components
	vector< vector<Point> > contours;
	findContours(src, contours, // original image and vector of contours
		RETR_EXTERNAL, CHAIN_APPROX_NONE); // retrival the external contours and retrival all pixels of each contours

	// Print contours's length
	cout << "Contours : " << contours.size() << endl;

	vector <vector <Point> >::const_iterator itContours = contours.begin();
	while (itContours != contours.end()) {
		cout << "Size: " << itContours->size() << endl;
		++itContours;
	}

	for (int i = 0; i < contours.size(); i++) {
		cout << "area of " << i << " = " << contourArea(contours[i]) << endl;
	}

	// draw black contours on white image
	Mat dst(src.size(), CV_8U, Scalar(255));
	for (int i = 0; i < contours.size(); i++) {
		drawContours(dst, contours, i, Scalar(0), 2);

	}
	/*	drawContours(result, contours,
			-1, // draw all contours
			Scalar(0), // in black
			2); // with a thickness of 2
	*/
	// Elliminate too short or too long contours
	int cMin = 50; // minimum contours length
	int cMax = 1000; // maximum contours length

	vector <vector <Point> >::const_iterator itc = contours.begin();
	while (itc != contours.end()) {
		if (itc->size() < cMin || itc->size() > cMax)
			itc = contours.erase(itc);
		else
			++itc;
	}

	// draw contours on the original image
	Mat original = imread("../images/group.jpg");
	drawContours(original, contours, -1, Scalar(255, 255, 255), 2);
	namedWindow("Contours on Animals");
	imshow("Contours on Animals", original);

	// Let's now draw black contours on white image
	dst.setTo(Scalar(255));
	drawContours(dst, contours, -1, 0, 1);

	namedWindow("Contours");	imshow("Contours", dst);

	// testing the bounding box
	Rect r0 = boundingRect(contours[0]);
	// draw the rectangle
	rectangle(dst, r0, 0, 2);

	// testing the enclosing circle
	float radius;
	Point2f center;
	minEnclosingCircle(contours[1], center, radius);
	cout << "Center (x, y) : " << center.x << " , " << center.y << endl;
	circle(dst, center, radius, 0, 2);

	// testing the approximate polygon
	vector <Point> poly;
	approxPolyDP(contours[2], poly, 5, true);
	polylines(dst, poly, true, 0, 2); // draw the polygon
	cout << "Polygon size : " << poly.size() << endl;

	// testing the convex hull
	vector <Point> hull;
	convexHull(contours[3], hull, false, true);
	polylines(dst, hull, true, 0, 2); // draw the polygon

	// convexityDefects()
	vector <int> hullIndices;
	convexHull(contours[3], hullIndices, false, false);
	vector <Vec4i> defects;
	convexityDefects(contours[3], hullIndices, defects);

	vector <Vec4i>::const_iterator cd = defects.begin();
	for (int i = 0; cd != defects.end(); i++) {
		cout << "defects[" << i << "] : " << (*cd) << endl;
		++cd;
	}

	// testing the moments
	itc = contours.begin();
	while (itc != contours.end()) {
		// compute all moments
		Moments mom = moments(*itc++);
		// draw mass center
		circle(dst, Point(mom.m10 / mom.m00, mom.m01 / mom.m00),
			2, Scalar(0), 2);
	}

	namedWindow("Shape");
	imshow("Shape", dst);

	waitKey();
	return 0;
}
