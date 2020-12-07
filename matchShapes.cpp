#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat ref_src, ref_gray, ref_bin;
	ref_src = imread("../images/refShapes.jpg");
	cvtColor(ref_src, ref_gray, COLOR_BGR2GRAY);//그레이레벨로 변환
	threshold(ref_gray, ref_bin, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);//오츄이진화

	Mat test_src, test_gray, test_bin;
	test_src = imread("../images/testShapes1.jpg");
	cvtColor(test_src, test_gray, COLOR_BGR2GRAY);//그레이레벨로 변환
	threshold(test_gray, test_bin, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);//오츄이진화

	// findContours() of ref. image
	vector < vector<Point> > contours_ref, contours_test;
	findContours(ref_bin, contours_ref, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	findContours(test_bin, contours_test, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	Mat ref_dst(ref_src.size(), CV_8UC3, Scalar(0, 0, 0));//채널 3개, 기본값 검정색
	Scalar  colorTable[] = { Scalar(0, 0, 255), //색 확인차 색 지정
		Scalar(0, 255, 0),
		Scalar(255, 0, 0) };

	for (int i = 0; i < contours_ref.size(); i++) {
		//drawContours(ref_dst, contours_ref, i, Scalar(rand()%256, rand()%256, rand()%256), 2);
		//주석은 임의 색 지정
		drawContours(ref_dst, contours_ref, i, Scalar(colorTable[i]), 2);
	}

	// shape matching
	Mat test_dst(test_src.size(), CV_8UC3, Scalar(0, 0, 0));
	for (int i = 0; i < contours_test.size(); i++) {
		double d[3]; double minK = 1000000.0;	int index = 0;//가장 작은 값 찾기 위함
		for (int j = 0; j < contours_ref.size(); j++) {
			d[j] = matchShapes(contours_test[i], contours_ref[j], CONTOURS_MATCH_I1, 0);
			//가장 작은 값 찾아 매치
			cout << "d[" << j << "] = " << d[j] << endl;
			if (d[j] < minK) {
				minK = d[j];
				index = j;
			}
			cout << "index = " << index << endl;
		}
		drawContours(test_dst, contours_test, i, colorTable[index], 2); //찾아 준 값과 같은 색으로 지정
	}

	imshow("ref_bin", ref_bin); imshow("test_bin", test_bin);
	imshow("ref_dst", ref_dst);	imshow("test_dst", test_dst);
	waitKey();
	return 0;
}
