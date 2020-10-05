#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	uchar data[] = {
		0,0,1,1,0,0,0,0,
		1,1,1,1,0,0,1,0,
		1,1,1,1,0,0,0,0,
		0,0,0,0,0,1,1,0,
		0,0,0,1,1,1,1,0,
		0,0,0,1,0,0,1,0,
		0,0,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,
	};

	Mat src = Mat(8, 8, CV_8UC1, data) * 255; //255로 출력되는 부분이 흰 부분
	Mat label1;
	int cnt1 = connectedComponents(src, label1); //연결요소 계산해주는 함수. 개수 리턴
	cout << "src:\n" << src << endl;
	cout << "labels:\n" << label1 << endl;
	cout << "number of labels: " << cnt1 << endl;
	//기본적으로는 8방향 출력
	return 0;
}
